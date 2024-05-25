#pragma once

#include <string>

namespace delivery::core::domain::order_aggregate {

// TODO (dymons) Use smart enum

enum class OrderStatus {
  Created,
  Assigned,
  Completed,
};

[[nodiscard]] auto ToString(OrderStatus status) -> std::string;
[[nodiscard]] auto FromString(std::string_view status) -> OrderStatus;

}  // namespace delivery::core::domain::order
