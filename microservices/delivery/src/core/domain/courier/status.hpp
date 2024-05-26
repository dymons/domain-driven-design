#pragma once

#include <string>

namespace delivery::core::domain::courier {

// TODO (dymons) Use smart enum

enum class Status {
  NotAvailable,
  Ready,
  Busy,
};

[[nodiscard]] auto ToString(Status status) -> std::string;
[[nodiscard]] auto FromString(std::string_view status) -> Status;

}  // namespace delivery::core::domain::courier
