#include "courier.hpp"

#include <userver/utils/uuid7.hpp>
#include <utility>

namespace delivery::core::domain::courier {

auto Courier::Create(CourierName name, Transport transport) -> Courier {
  if (name.GetUnderlying().empty()) {
    throw ArgumentException{"Courier name should not be empty"};
  }

  return {CourierId{userver::utils::generators::GenerateUuidV7()},
          std::move(name), std::move(transport),
          shared_kernel::Location::kMinLocation, Status::NotAvailable};
}

auto Courier::Hydrate(CourierId id, CourierName name, Transport transport,
                      shared_kernel::Location current_location, Status status)
    -> Courier {
  return {std::move(id), std::move(name), std::move(transport),
          current_location, status};
}

auto Courier::GetId() const noexcept -> CourierId { return id_; }

auto Courier::GetName() const noexcept -> CourierName { return name_; }

auto Courier::GetTransport() const noexcept -> Transport { return transport_; }

auto Courier::GetCurrentLocation() const noexcept -> shared_kernel::Location {
  return current_location_;
}

auto Courier::GetStatus() const noexcept -> Status { return status_; }

auto Courier::MoveTo(shared_kernel::Location const to_location) -> void {
  if (current_location_ == to_location) {
    return;
  }

  auto cruise_range = transport_.GetSpeed().GetUnderlying();

  auto new_x = current_location_.GetX();
  if (new_x != to_location.GetX()) {
    new_x = shared_kernel::X{
        std::min(current_location_.GetX().GetUnderlying() + cruise_range,
                 to_location.GetX().GetUnderlying())};
    cruise_range -= (to_location.GetX().GetUnderlying() -
                     current_location_.GetX().GetUnderlying());
  }

  auto new_y = current_location_.GetY();
  if (new_y != to_location.GetY() && cruise_range > 0) {
    new_y = shared_kernel::Y{
        std::min(current_location_.GetY().GetUnderlying() + cruise_range,
                 to_location.GetY().GetUnderlying())};
  }

  auto reached_location = shared_kernel::Location::Create(new_x, new_y);

  if (status_ == Status::Busy && reached_location == to_location) {
    status_ = Status::Ready;
  }

  current_location_ = reached_location;
}

auto Courier::StartWork() -> void {
  if (status_ == Status::Busy) {
    throw TryStartWorkingWhenAlreadyStarted{};
  }

  status_ = Status::Ready;
}

auto Courier::StopWork() -> void {
  if (status_ == Status::Busy) {
    throw TryStopWorkingWithIncompleteDelivery{};
  }

  status_ = Status::NotAvailable;
}

auto Courier::InWork() -> void {
  if (status_ == Status::NotAvailable) {
    throw TryAssignOrderWhenNotAvailable{};
  }
  if (status_ == Status::Busy) {
    throw TryAssignOrderWhenCourierHasAlreadyBusy{};
  }

  status_ = Status::Busy;
}

auto Courier::CalculateTimeToPoint(
    shared_kernel::Location location) const noexcept -> Time {
  auto const distance = current_location_.DistanceTo(location);
  return Time{static_cast<double>(distance.GetUnderlying()) /
              static_cast<double>(transport_.GetSpeed().GetUnderlying())};
}

}  // namespace delivery::core::domain::courier
