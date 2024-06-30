#include "status.hpp"

#include <userver/utils/exception.hpp>
#include <userver/utils/trivial_map.hpp>

#include "exceptions.hpp"

namespace delivery::core::domain::courier {

namespace {

constexpr userver::utils::TrivialBiMap kCourierStatusMapping =
    [](auto selector) {
      return selector()
          .Case(std::string_view{"not_available"}, CourierStatus::kNotAvailable)
          .Case(std::string_view{"ready"}, CourierStatus::kReady)
          .Case(std::string_view{"busy"}, CourierStatus::kBusy);
    };

}  // namespace

const CourierStatus CourierStatus::kNotAvailable =
    CourierStatus{CourierStatus::Status::NotAvailable};

const CourierStatus CourierStatus::kReady =
    CourierStatus{CourierStatus::Status::Ready};

const CourierStatus CourierStatus::kBusy =
    CourierStatus{CourierStatus::Status::Busy};

CourierStatus::CourierStatus(Status const status) : status_{status} {}

auto CourierStatus::ToString() const -> std::string {
  auto const status_as_string = kCourierStatusMapping.TryFindBySecond(*this);
  if (not status_as_string.has_value()) {
    userver::utils::LogErrorAndThrow<ArgumentException>(
        "Cant convert status to std::string");
  }

  return std::string{status_as_string.value()};
}

auto CourierStatus::FromString(std::string_view const status) -> CourierStatus {
  auto const status_as_enum = kCourierStatusMapping.TryFindByFirst(status);
  if (not status_as_enum.has_value()) {
    userver::utils::LogErrorAndThrow<ArgumentException>(
        "Cant convert to CourierStatus");
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
