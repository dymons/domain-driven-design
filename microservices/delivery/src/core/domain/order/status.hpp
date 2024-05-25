#pragma once

#include <string>

namespace delivery::core::domain::order {

// TODO (dymons) Use smart enum

enum class Status {
  Created,
  Assigned,
  Completed,
};

[[nodiscard]] auto ToString(Status status) -> std::string;
[[nodiscard]] auto FromString(std::string_view status) -> Status;

}  // namespace delivery::core::domain::order
