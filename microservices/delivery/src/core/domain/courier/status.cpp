#include "status.hpp"

#include <userver/utils/trivial_map.hpp>

#include "exceptions.hpp"

namespace delivery::core::domain::courier {

namespace {

constexpr userver::utils::TrivialBiMap kCourierStatusMapping =
    [](auto selector) {
      return selector()
          .Case(std::string_view{"not_available"},
                CourierStatus::Status::NotAvailable)
          .Case(std::string_view{"ready"}, CourierStatus::Status::Ready)
          .Case(std::string_view{"busy"}, CourierStatus::Status::Busy);
    };

}  // namespace

CourierStatus::CourierStatus(Status const status) : status_{status} {}

auto CourierStatus::ToString() const -> std::string {
  auto const status_as_string = kCourierStatusMapping.TryFindBySecond(status_);
  if (not status_as_string.has_value()) {
    throw ArgumentException{"Cant convert status std::string"};
  }

  return std::string{status_as_string.value()};
}

auto CourierStatus::FromString(std::string_view const status) -> CourierStatus {
  auto const status_as_enum = kCourierStatusMapping.TryFindByFirst(status);
  if (not status_as_enum.has_value()) {
    throw ArgumentException{"Cant convert to CourierStatus"};
  }

  return CourierStatus{status_as_enum.value()};
}

auto CourierStatus::IsNotAvailable() const noexcept -> bool {
  return status_ == Status::NotAvailable;
}

auto CourierStatus::IsReady() const noexcept -> bool {
  return status_ == Status::Ready;
}

auto CourierStatus::IsBusy() const noexcept -> bool {
  return status_ == Status::Busy;
}

}  // namespace delivery::core::domain::courier
