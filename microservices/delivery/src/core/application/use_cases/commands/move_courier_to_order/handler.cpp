#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>
#include <core/ports/courier_repository/irepository.hpp>
#include <core/ports/order_repository/irepository.hpp>
#include <core/ports/unit_of_work/irun_transaction_context.hpp>
#include <core/ports/unit_of_work/iunit_of_work.hpp>
#include <utils/container.hpp>
#include <utils/optional.hpp>

#include "command.hpp"
#include "ihandler.hpp"

// clang-format off
namespace delivery::core::application::use_cases::commands::move_courier_to_order {
// clang-format on

namespace {

class MoveCourierToOrderHandler final : public IMoveCourierToOrderHandler {
 public:
  ~MoveCourierToOrderHandler() final = default;

  MoveCourierToOrderHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository,
      SharedRef<core::ports::IOrderRepository> order_repository,
      SharedRef<core::ports::IUnitOfWork> unit_of_work)
      : courier_repository_{std::move(courier_repository)},
        order_repository_{std::move(order_repository)},
        unit_of_work_{std::move(unit_of_work)} {}

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

        this->unit_of_work_->RunTransaction([&](const auto& context) {
          context->GetOrderRepository()->Update(order);
          context->GetCourierRepository()->Update(courier);
        });
      });
    });
  }

 private:
  SharedRef<core::ports::ICourierRepository> const courier_repository_;
  SharedRef<core::ports::IOrderRepository> const order_repository_;
  SharedRef<core::ports::IUnitOfWork> const unit_of_work_;
};

}  // namespace

auto MakeAssignOrdersHandler(
    SharedRef<core::ports::ICourierRepository> courier_repository,
    SharedRef<core::ports::IOrderRepository> order_repository,
    SharedRef<core::ports::IUnitOfWork> unit_of_work)
    -> SharedRef<IMoveCourierToOrderHandler> {
  return delivery::MakeSharedRef<MoveCourierToOrderHandler>(
      std::move(courier_repository), std::move(order_repository),
      std::move(unit_of_work));
}

// clang-format off
}  // namespace delivery::core::application::use_cases::commands::move_courier_to_order
// clang-format on
