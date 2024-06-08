#include "order.hpp"

#include <core/domain/order/order.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(core::domain::order::Order const& order) -> Order {
  return {
      .id = order.GetId(),
      .status = order.GetStatus().ToString(),
      .courier_id = order.GetCourierId(),
      .delivery_location = dto::Convert(order.GetDeliveryLocation()),
      .weight = dto::Convert(order.GetWeight()),
  };
}

auto Convert(Order const& order) -> core::domain::order::Order {
  return core::domain::order::Order::Hydrate(
      order.id, core::domain::order::OrderStatus::FromString(order.status),
      order.courier_id, dto::Convert(order.delivery_location),
      dto::Convert(order.weight));
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
