#include "order.hpp"

#include <userver/utils/exception.hpp>

#include "exceptions.hpp"

namespace delivery::core::domain::order {

auto Order::Create(BasketId basket_id, Location delivery_location,
                   Weight weight) -> MutableSharedRef<Order> {
  return MakeMutableSharedRef<Order>(
      Order{OrderId{std::move(basket_id).GetUnderlying()},
            OrderStatus::kCreated, std::nullopt, delivery_location, weight});
}

auto Order::Hydrate(OrderId id, OrderStatus status,
                    std::optional<CourierId> courier_id,
                    Location delivery_location, Weight weight)
    -> MutableSharedRef<Order> {
  return MakeMutableSharedRef<Order>(Order{
      std::move(id), status, std::move(courier_id), delivery_location, weight});
}

auto Order::GetId() const noexcept -> OrderId { return id_; }

auto Order::GetStatus() const noexcept -> OrderStatus { return status_; }

auto Order::GetCourierId() const noexcept -> std::optional<CourierId> {
  return courier_id_;
}

auto Order::GetDeliveryLocation() const noexcept -> Location {
  return delivery_location_;
}

auto Order::GetWeight() const noexcept -> Weight { return weight_; }

auto Order::IsCourierAssigned() const noexcept -> bool {
  return courier_id_.has_value();
}

auto Order::AssignCourier(CourierId const& courier_id) -> void {
  status_ = OrderStatus::kAssigned;
  courier_id_ = courier_id;
}

auto Order::Complete() -> void {
  if (not IsCourierAssigned()) {
    userver::utils::LogErrorAndThrow<CantCompletedNotAssignedOrder>(
        "Only the assigned order can be completed");
  }

  status_ = OrderStatus::kCompleted;
}

}  // namespace delivery::core::domain::order
