#include "status.hpp"

#include <userver/utils/trivial_map.hpp>
#include <userver/utils/exception.hpp>

#include "exceptions.hpp"

namespace delivery::core::domain::order {

namespace {

constexpr userver::utils::TrivialBiMap kOrderStatusMapping = [](auto selector) {
  return selector()
      .Case(std::string_view{"created"}, OrderStatus::kCreated)
      .Case(std::string_view{"assigned"}, OrderStatus::kAssigned)
      .Case(std::string_view{"completed"}, OrderStatus::kCompleted);
};

}  // namespace

const OrderStatus OrderStatus::kCreated =
    OrderStatus{OrderStatus::Status::Created};

const OrderStatus OrderStatus::kAssigned =
    OrderStatus{OrderStatus::Status::Assigned};

const OrderStatus OrderStatus::kCompleted =
    OrderStatus{OrderStatus::Status::Completed};

OrderStatus::OrderStatus(Status const status) : status_{status} {}

auto OrderStatus::ToString() const -> std::string {
  auto const status_as_string = kOrderStatusMapping.TryFindBySecond(*this);
  if (not status_as_string.has_value()) {
    userver::utils::LogErrorAndThrow<ArgumentException>(
        "Cant convert status std::string");
  }

  return std::string{status_as_string.value()};
}

auto OrderStatus::FromString(std::string_view const status) -> OrderStatus {
  auto const status_as_enum = kOrderStatusMapping.TryFindByFirst(status);
  if (not status_as_enum.has_value()) {
    userver::utils::LogErrorAndThrow<ArgumentException>(
        "Cant convert to OrderStatus");
  }

  return status_as_enum.value();
}

auto OrderStatus::IsCreated() const noexcept -> bool {
  return status_ == Status::Created;
}

auto OrderStatus::IsAssigned() const noexcept -> bool {
  return status_ == Status::Assigned;
}

auto OrderStatus::IsCompleted() const noexcept -> bool {
  return status_ == Status::Completed;
}

}  // namespace delivery::core::domain::order
