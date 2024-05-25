#pragma once

#include <string>

namespace delivery::core::domain::courier_aggregate {

// TODO (dymons) Use smart enum

enum class CourierStatus {
  NotAvailable,
  Ready,
  Busy,
};

[[nodiscard]] auto ToString(CourierStatus status) -> std::string;
[[nodiscard]] auto FromString(std::string_view status) -> CourierStatus;

}  // namespace delivery::core::domain::courier_aggregate
