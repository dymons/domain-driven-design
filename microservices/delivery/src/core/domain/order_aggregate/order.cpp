#include "order.hpp"

#include "exceptions.hpp"

namespace delivery::core::domain::order_aggregate {

auto Order::Create(BasketId basket_id, shared_kernel::Location location,
                   shared_kernel::Weight weight) -> Order {
  return {OrderId{basket_id.GetUnderlying()}, OrderStatus::Created,
          std::nullopt, location, weight};
}

auto Order::GetOrderId() const noexcept -> OrderId { return order_id_; }

auto Order::GetOrderStatus() const noexcept -> OrderStatus { return status_; }

auto Order::GetCourierId() const noexcept -> std::optional<CourierId> {
  return courier_id_;
}

auto Order::GetLocation() const noexcept -> shared_kernel::Location {
  return location_;
}

auto Order::GetWeight() const noexcept -> shared_kernel::Weight {
  return weight_;
}

auto Order::IsCourierAssigned() const noexcept -> bool {
  return courier_id_.has_value();
}

auto Order::AssignCourier(CourierId courier_id) -> void {
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
