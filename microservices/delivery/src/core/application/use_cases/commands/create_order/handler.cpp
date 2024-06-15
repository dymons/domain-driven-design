#include "handler.hpp"

#include <core/domain/order/order.hpp>

namespace delivery::application::use_cases::commands::create_order {

CreateOrderHandler::CreateOrderHandler(
    SharedRef<core::ports::IOrderRepository> order_repository)
    : order_repository_(std::move(order_repository)) {}

auto CreateOrderHandler::Handle(CreateOrderCommand&& command) -> void {
  auto const order = core::domain::order::Order::Create(
      core::domain::order::BasketId{command.GetBasketId()},
      core::domain::Location::kMinLocation,
      core::domain::Weight{command.GetWeight()});

  try {
    order_repository_->Add(order);
  } catch (core::ports::OrderAlreadyExists const&) {
  }
}

}  // namespace delivery::application::use_cases::commands::api_v1_orders
