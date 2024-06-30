#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>
#include <core/ports/courier_repository/irepository.hpp>
#include <core/ports/order_repository/irepository.hpp>
#include <utils/container.hpp>
#include <utils/optional.hpp>

// clang-format off
namespace delivery::core::application::use_cases::commands::move_courier_to_order {
// clang-format on
namespace {

class MoveCourierToOrderHandler final : public IMoveCourierToOrderHandler {
 public:
  ~MoveCourierToOrderHandler() final = default;

  MoveCourierToOrderHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository,
      SharedRef<core::ports::IOrderRepository> order_repository)
      : courier_repository_(std::move(courier_repository)),
        order_repository_(std::move(order_repository)) {}

  auto Handle(MoveCourierToOrderCommand&&) const -> void final {
    auto order = container::FirstOrNullopt(order_repository_->GetAssigned());
    optional::map(std::move(order), [this](auto&& order) {
      auto courier = order->GetCourierId().transform([this](auto courier_id) {
        return this->courier_repository_->GetById(courier_id);
      });

      if (not courier.has_value()) {
        // TODO (dymons) Inconsistency State
      }

      optional::map(std::move(courier), [&, this](auto&& courier) {
        courier->MoveTo(order->GetDeliveryLocation());

        if (order->GetDeliveryLocation() == courier->GetCurrentLocation()) {
          order->Complete();
          courier->CompleteOrder();
        }

        // TODO (dymons) Use UnitOfWork
        this->order_repository_->Update(order);
        this->courier_repository_->Update(courier);
      });
    });
  }

 private:
  SharedRef<core::ports::ICourierRepository> const courier_repository_;
  SharedRef<core::ports::IOrderRepository> const order_repository_;
};

}  // namespace

auto MakeAssignOrdersHandler(
    SharedRef<core::ports::ICourierRepository> courier_repository,
    SharedRef<core::ports::IOrderRepository> order_repository)
    -> SharedRef<IMoveCourierToOrderHandler> {
  return userver::utils::MakeSharedRef<const MoveCourierToOrderHandler>(
      std::move(courier_repository), std::move(order_repository));
}

// clang-format off
}  // namespace delivery::core::application::use_cases::commands::move_courier_to_order
// clang-format on
