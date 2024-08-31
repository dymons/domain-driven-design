#include "courier.hpp"

#include <utility>

#include <userver/utils/exception.hpp>
#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::courier {

auto Courier::Create(CourierName name, Transport transport)
    -> MutableSharedRef<Courier> {
  if (name.GetUnderlying().empty()) {
    userver::utils::LogErrorAndThrow<ArgumentException>(
        "Courier name should not be empty");
  }

  return MakeMutableSharedRef<Courier>(
      Courier{CourierId{userver::utils::generators::GenerateUuidV7()},
              std::move(name), std::move(transport), Location::kMinLocation,
              CourierStatus::kNotAvailable});
}

auto Courier::Hydrate(CourierId id, CourierName name, Transport transport,
                      Location current_location, CourierStatus status)
    -> MutableSharedRef<Courier> {
  return MakeMutableSharedRef<Courier>(Courier{std::move(id), std::move(name),
                                               std::move(transport),
                                               current_location, status});
}

auto Courier::GetId() const noexcept -> CourierId { return id_; }

auto Courier::GetName() const noexcept -> CourierName { return name_; }

auto Courier::GetTransport() const noexcept -> Transport { return transport_; }

auto Courier::GetCurrentLocation() const noexcept -> Location {
  return current_location_;
}

auto Courier::GetStatus() const noexcept -> CourierStatus { return status_; }

auto Courier::operator==(const Courier& that) const -> bool {
  return this->GetId() == that.GetId();
}

auto Courier::MoveTo(Location const to_location) -> void {
  if (current_location_ == to_location) {
    return;
  }

  auto cruise_range = transport_.GetSpeed().GetUnderlying();

  auto new_x = current_location_.GetX();
  if (new_x != to_location.GetX()) {
    new_x =
        XCoord{std::min(current_location_.GetX().GetUnderlying() + cruise_range,
                        to_location.GetX().GetUnderlying())};
    cruise_range -= (to_location.GetX().GetUnderlying() -
                     current_location_.GetX().GetUnderlying());
  }

  auto new_y = current_location_.GetY();
  if (new_y != to_location.GetY() && cruise_range > 0) {
    new_y =
        YCoord{std::min(current_location_.GetY().GetUnderlying() + cruise_range,
                        to_location.GetY().GetUnderlying())};
  }

  auto reached_location = Location{new_x, new_y};
  if (status_.IsBusy() && reached_location == to_location) {
    status_ = CourierStatus::kReady;
  }

  current_location_ = reached_location;
}

auto Courier::StartWork() -> void {
  if (status_.IsBusy()) {
    userver::utils::LogErrorAndThrow<TryStartWorkingWhenAlreadyStarted>(
        "You cannot start work if it has already been started earlier");
  }

  status_ = CourierStatus::kReady;
}

auto Courier::StopWork() -> void {
  if (status_.IsBusy()) {
    userver::utils::LogErrorAndThrow<TryStopWorkingWithIncompleteDelivery>(
        "You cannot stop working if there is an incomplete delivery");
  }

  status_ = CourierStatus::kNotAvailable;
}

auto Courier::InWork() -> void {
  if (status_.IsNotAvailable()) {
    userver::utils::LogErrorAndThrow<TryAssignOrderWhenNotAvailable>(
        "You cannot take an order to work if the courier has not started the "
        "working day");
  }
  if (status_.IsBusy()) {
    userver::utils::LogErrorAndThrow<TryAssignOrderWhenCourierHasAlreadyBusy>(
        "You can't take an order to work if the courier is already busy");
  }

  status_ = CourierStatus::kBusy;
}

auto Courier::CompleteOrder() -> void { status_ = CourierStatus::kReady; }

auto Courier::CalculateTimeToPoint(Location location) const noexcept -> Time {
  auto const distance = current_location_.DistanceTo(location);
  return Time{static_cast<double>(distance.GetUnderlying()) /
              static_cast<double>(transport_.GetSpeed().GetUnderlying())};
}

}  // namespace delivery::core::domain::courier
