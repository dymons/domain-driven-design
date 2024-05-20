#pragma once

#include <string>

namespace delivery::core::domain::order_aggregate {

enum class OrderStatus {
  Created,
  Assigned,
  Completed,
};

auto ToString(OrderStatus status) -> std::string;
auto FromString(std::string_view status) -> OrderStatus;

}  // namespace delivery::core::domain::order_aggregate
