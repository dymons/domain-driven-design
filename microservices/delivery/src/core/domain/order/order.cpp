#include "order.hpp"

#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>
#include "exceptions.hpp"

namespace delivery::core::domain::order {

auto Order::Create(BasketId basket_id,
                   shared_kernel::Location delivery_location,
                   shared_kernel::Weight weight) -> Order {
  return {OrderId{std::move(basket_id).GetUnderlying()}, Status::Created,
          std::nullopt, delivery_location, weight};
}

auto Order::GetId() const noexcept -> OrderId { return id_; }

auto Order::GetStatus() const noexcept -> Status { return status_; }

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
  if (courier.GetStatus() == courier::Status::Busy) {
    userver::utils::LogErrorAndThrow<CantAssignOrderToBusyCourier>(
        "Courier is busy, can't assign courier to the order");
  }

  courier.InWork();

  status_ = Status::Assigned;
  courier_id_ = courier.GetId();
}

auto Order::Complete() -> void {
  if (not IsCourierAssigned()) {
    userver::utils::LogErrorAndThrow<CantCompletedNotAssignedOrder>(
        "Only the assigned order can be completed");
  }

  status_ = Status::Completed;
}

}  // namespace delivery::core::domain::order
