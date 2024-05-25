#include "order.hpp"

#include <core/domain/courier/courier.hpp>

namespace delivery::core::domain::order_aggregate {

auto Order::Create(BasketId basket_id,
                   shared_kernel::Location delivery_location,
                   shared_kernel::Weight weight) -> Order {
  return {OrderId{std::move(basket_id).GetUnderlying()}, OrderStatus::Created,
          std::nullopt, delivery_location, weight};
}

auto Order::GetId() const -> OrderId { return id_; }

auto Order::GetStatus() const -> OrderStatus { return status_; }

auto Order::GetCourierId() const -> std::optional<courier::CourierId> {
  return courier_id_;
}

auto Order::GetDeliveryLocation() const -> shared_kernel::Location {
  return delivery_location_;
}

auto Order::GetWeight() const -> shared_kernel::Weight { return weight_; }

auto Order::IsCourierAssigned() const -> bool {
  return courier_id_.has_value();
}

// TODO (dymons) Use domain event for eventual consistency to assign courier?
auto Order::AssignCourier(courier::Courier& courier) -> void {
  if (courier.GetStatus() == courier::CourierStatus::Busy) {
    throw CantAssignOrderToBusyCourier{};
  }

  courier.InWork();

  status_ = OrderStatus::Assigned;
  courier_id_ = courier.GetId();
}

auto Order::Complete() -> void {
  if (not IsCourierAssigned()) {
    throw CantCompletedNotAssignedOrder{};
  }

  status_ = OrderStatus::Completed;
}

}  // namespace delivery::core::domain::order_aggregate
