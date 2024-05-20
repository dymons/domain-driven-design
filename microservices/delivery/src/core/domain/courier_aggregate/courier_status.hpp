#pragma once

#include <string>

namespace delivery::core::domain::courier_aggregate {

enum class CourierStatus {
  NotAvailable,
  Ready,
  Busy,
};

auto ToString(CourierStatus status) -> std::string;
auto FromString(std::string_view status) -> CourierStatus;

}  // namespace delivery::core::domain::courier_aggregate
