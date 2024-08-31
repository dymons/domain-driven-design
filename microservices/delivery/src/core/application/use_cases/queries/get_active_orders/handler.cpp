#include "handler.hpp"

#include <core/domain/order/order.hpp>
#include <core/ports/order_repository/irepository.hpp>

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

namespace {

class GetActiveOrdersHandler final : public IGetActiveOrdersHandler {
 public:
  ~GetActiveOrdersHandler() final = default;

  explicit GetActiveOrdersHandler(
      SharedRef<core::ports::IOrderRepository> order_repository)
      : order_repository_(std::move(order_repository)) {}

  auto Handle(GetActiveOrdersQuery&&) const -> Response final {
    auto orders = order_repository_->GetOrders();

    auto response = Response200{};
    response.orders.reserve(orders.size());
    for (auto&& order : orders) {
      if (order->GetStatus().IsCompleted()) {
        continue;
      }

      response.orders.emplace_back(
          order->GetId().GetUnderlying(),
          Location{order->GetDeliveryLocation().GetX().GetUnderlying(),
                   order->GetDeliveryLocation().GetY().GetUnderlying()});
    }

    return std::move(response);
  }

 private:
  SharedRef<core::ports::IOrderRepository> const order_repository_;
};

}  // namespace

auto MakeGetActiveOrdersHandler(
    SharedRef<core::ports::IOrderRepository> order_repository)
    -> SharedRef<IGetActiveOrdersHandler> {
  return delivery::MakeSharedRef<GetActiveOrdersHandler>(
      std::move(order_repository));
}

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
