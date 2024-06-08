#include "status.hpp"

#include <userver/utils/trivial_map.hpp>

#include "exceptions.hpp"

namespace delivery::core::domain::courier {

namespace {

constexpr userver::utils::TrivialBiMap kCourierStatusMapping =
    [](auto selector) {
      return selector()
          .Case(std::string_view{"not_available"}, Status::NotAvailable)
          .Case(std::string_view{"ready"}, Status::Ready)
          .Case(std::string_view{"busy"}, Status::Busy);
    };

}  // namespace

auto ToString(Status const status) -> std::string {
  auto const status_as_string = kCourierStatusMapping.TryFindBySecond(status);
  if (not status_as_string.has_value()) {
    throw ArgumentException{"Cant convert status std::string"};
  }

  return std::string{status_as_string.value()};
}

auto FromString(std::string_view const status) -> Status {
  auto const status_as_enum = kCourierStatusMapping.TryFindByFirst(status);
  if (not status_as_enum.has_value()) {
    throw ArgumentException{"Cant convert to CourierStatus"};
  }

  return status_as_enum.value();
}

}  // namespace delivery::core::domain::courier
