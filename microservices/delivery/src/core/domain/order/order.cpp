#include "order.hpp"

#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>
#include <utility>
#include "exceptions.hpp"

namespace delivery::core::domain::order {

auto Order::Create(BasketId basket_id,
                   shared_kernel::Location delivery_location,
                   shared_kernel::Weight weight) -> Order {
  return {OrderId{std::move(basket_id).GetUnderlying()}, OrderStatus::kCreated,
          std::nullopt, delivery_location, weight};
}

auto Order::Hydrate(OrderId id, OrderStatus status,
                    std::optional<courier::CourierId> courier_id,
                    shared_kernel::Location delivery_location,
                    shared_kernel::Weight weight) -> Order {
  return {std::move(id), status, std::move(courier_id), delivery_location,
          weight};
}

auto Order::GetId() const noexcept -> OrderId { return id_; }

auto Order::GetStatus() const noexcept -> OrderStatus { return status_; }

auto Order::GetCourierId() const noexcept -> std::optional<courier::CourierId> {
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

auto Order::AssignCourier(courier::Courier& courier) -> void {
  if (courier.GetStatus().IsBusy()) {
    userver::utils::LogErrorAndThrow<CantAssignOrderToBusyCourier>(
        "Courier is busy, can't assign courier to the order");
  }

  courier.InWork();

  status_ = OrderStatus::kAssigned;
  courier_id_ = courier.GetId();
}

auto Order::Complete() -> void {
  if (not IsCourierAssigned()) {
    userver::utils::LogErrorAndThrow<CantCompletedNotAssignedOrder>(
        "Only the assigned order can be completed");
  }

  status_ = OrderStatus::kCompleted;
}

}  // namespace delivery::core::domain::order
