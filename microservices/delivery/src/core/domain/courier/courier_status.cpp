#include "courier_status.hpp"

#include <userver/utils/trivial_map.hpp>

#include "exceptions.hpp"

namespace delivery::core::domain::courier {

namespace {

constexpr userver::utils::TrivialBiMap kCourierStatusMapping =
    [](auto selector) {
      return selector()
          .Case(std::string_view{"not_available"}, CourierStatus::NotAvailable)
          .Case(std::string_view{"ready"}, CourierStatus::Ready)
          .Case(std::string_view{"busy"}, CourierStatus::Busy);
    };

}  // namespace

auto ToString(CourierStatus const status) -> std::string {
  auto const status_as_string = kCourierStatusMapping.TryFindBySecond(status);
  if (not status_as_string.has_value()) {
    throw ArgumentException{"Cant convert status std::string"};
  }

  return std::string{status_as_string.value()};
}

auto FromString(std::string_view const status) -> CourierStatus {
  auto const status_as_enum = kCourierStatusMapping.TryFindByFirst(status);
  if (not status_as_enum.has_value()) {
    throw ArgumentException{"Cant convert to CourierStatus"};
  }

  return status_as_enum.value();
}

}  // namespace delivery::core::domain::courier
