#include "status.hpp"

#include <userver/utils/trivial_map.hpp>

#include "exceptions.hpp"

namespace delivery::core::domain::order {

namespace {

constexpr userver::utils::TrivialBiMap kOrderStatusMapping = [](auto selector) {
  return selector()
      .Case(std::string_view{"created"}, Status::Created)
      .Case(std::string_view{"assigned"}, Status::Assigned)
      .Case(std::string_view{"completed"}, Status::Completed);
};

}  // namespace

auto ToString(Status const status) -> std::string {
  auto const status_as_string = kOrderStatusMapping.TryFindBySecond(status);
  if (not status_as_string.has_value()) {
    throw ArgumentException{"Cant convert status std::string"};
  }

  return std::string{status_as_string.value()};
}

auto FromString(std::string_view const status) -> Status {
  auto const status_as_enum = kOrderStatusMapping.TryFindByFirst(status);
  if (not status_as_enum.has_value()) {
    throw ArgumentException{"Cant convert to OrderStatus"};
  }

  return status_as_enum.value();
}

}  // namespace delivery::core::domain::order
