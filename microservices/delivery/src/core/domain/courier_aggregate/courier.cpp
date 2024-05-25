#include "courier.hpp"

#include <userver/utils/uuid7.hpp>
#include <utility>

namespace delivery::core::domain::courier_aggregate {

auto Courier::Create(CourierName name, Transport transport) -> Courier {
  if (name.GetUnderlying().empty()) {
    throw ArgumentException{"Courier name should not be empty"};
  }

  return {CourierId{userver::utils::generators::GenerateUuidV7()},
          std::move(name), std::move(transport),
          shared_kernel::Location::kMinLocation, CourierStatus::NotAvailable};
}

auto Courier::Hydrate(CourierId id, CourierName name, Transport transport,
                      shared_kernel::Location current_location,
                      CourierStatus status) -> Courier {
  return {std::move(id), std::move(name), std::move(transport),
          current_location, status};
}

auto Courier::GetId() const -> CourierId { return id_; }

auto Courier::GetName() const -> CourierName { return name_; }

auto Courier::GetTransport() const -> Transport { return transport_; }

auto Courier::GetCurrentLocation() const -> shared_kernel::Location {
  return current_location_;
}

auto Courier::GetStatus() const -> CourierStatus { return status_; }

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

  if (status_ == CourierStatus::Busy && reached_location == to_location) {
    status_ = CourierStatus::Ready;
  }

  current_location_ = reached_location;
}

auto Courier::StartWork() -> void {
  if (status_ == CourierStatus::Busy) {
    throw TryStartWorkingWhenAlreadyStarted{};
  }

  status_ = CourierStatus::Ready;
}

auto Courier::StopWork() -> void {
  if (status_ == CourierStatus::Busy) {
    throw TryStopWorkingWithIncompleteDelivery{};
  }

  status_ = CourierStatus::NotAvailable;
}

auto Courier::InWork() -> void {
  if (status_ == CourierStatus::NotAvailable) {
    throw TryAssignOrderWhenNotAvailable{};
  }
  if (status_ == CourierStatus::Busy) {
    throw TryAssignOrderWhenCourierHasAlreadyBusy{};
  }

  status_ = CourierStatus::Busy;
}

auto Courier::CalculateTimeToPoint(shared_kernel::Location location) -> Time {
  auto const distance = current_location_.DistanceTo(location);
  return Time{static_cast<double>(distance.GetUnderlying()) /
              static_cast<double>(transport_.GetSpeed().GetUnderlying())};
}

}  // namespace delivery::core::domain::courier_aggregate
