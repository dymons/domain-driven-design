#include "order.hpp"

#include "exceptions.hpp"

namespace delivery::core::domain::order_aggregate {

auto Order::Create(BasketId basket_id,
                   shared_kernel::Location delivery_location,
                   shared_kernel::Weight weight) -> Order {
  return {OrderId{basket_id.GetUnderlying()}, OrderStatus::Created,
          std::nullopt, delivery_location, weight};
}

auto Order::GetOrderId() const noexcept -> OrderId { return order_id_; }

auto Order::GetOrderStatus() const noexcept -> OrderStatus { return status_; }

auto Order::GetCourierId() const noexcept
    -> std::optional<courier_aggregate::CourierId> {
  return courier_id_;
}

auto Order::GetDeliveryLocation() const noexcept -> shared_kernel::Location {
  return delivery_location_;
}

auto Order::GetWeight() const noexcept -> shared_kernel::Weight {
  return weight_;
}

auto Order::IsCourierAssigned() const noexcept -> bool {
  return courier_id_.has_value();
}

auto Order::AssignCourier(courier_aggregate::CourierId courier_id) -> void {
  status_ = OrderStatus::Assigned;
  courier_id_ = std::move(courier_id);
}

auto Order::Complete() -> void {
  if (status_ != OrderStatus::Assigned) {
    throw IllegalStateException{"Only the assigned order can be completed"};
  }

  status_ = OrderStatus::Completed;
}

}  // namespace delivery::core::domain::order_aggregate
