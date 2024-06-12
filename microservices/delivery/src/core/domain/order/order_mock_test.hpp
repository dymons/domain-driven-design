#pragma once

#include "order.hpp"
#include "exceptions.hpp"

namespace delivery::core::domain::order {

[[nodiscard]] auto MockOrder() -> Order;

} // namespace delivery::core::domain::order
