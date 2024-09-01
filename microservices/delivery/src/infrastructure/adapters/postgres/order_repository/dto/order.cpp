#include "order.hpp"

#include <core/domain/order/order.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(SharedRef<core::domain::order::Order> const& order) -> Order {
  return {
      .id = order->GetId(),
      .status = order->GetStatus().ToString(),
      .courier_id = order->GetCourierId(),
      .delivery_location = dto::Convert(order->GetDeliveryLocation()),
      .weight = dto::Convert(order->GetWeight()),
  };
}

auto Convert(Order const& order)
    -> MutableSharedRef<core::domain::order::Order> {
  return core::domain::order::Order::Hydrate(
      order.id, core::domain::order::OrderStatus::FromString(order.status),
      order.courier_id, dto::Convert(order.delivery_location),
      dto::Convert(order.weight));
}

auto Convert(Order&& order) -> MutableSharedRef<core::domain::order::Order> {
  return core::domain::order::Order::Hydrate(
      std::move(order.id),
      core::domain::order::OrderStatus::FromString(std::move(order.status)),
      std::move(order.courier_id), dto::Convert(order.delivery_location),
      dto::Convert(order.weight));
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
