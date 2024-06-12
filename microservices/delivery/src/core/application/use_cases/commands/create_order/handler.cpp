#include "handler.hpp"

#include <core/domain/order/order.hpp>

namespace delivery::application::use_cases::commands::create_order {

Handler::Handler(SharedRef<core::ports::IOrderRepository> order_repository)
    : order_repository_(std::move(order_repository)) {}

auto Handler::Handle(Command&& command) -> void {
  auto const order = core::domain::order::Order::Create(
      core::domain::order::BasketId{command.basket_id.GetUnderlying()},
      core::domain::Location::kMinLocation,
      core::domain::Weight{command.weight.GetUnderlying()});

  try {
    order_repository_->Add(order);
  } catch (core::ports::OrderAlreadyExists const&) {
  }
}

}  // namespace delivery::application::use_cases::commands::create_order
