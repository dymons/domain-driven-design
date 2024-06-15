#pragma once

#include "order.hpp"
#include "exceptions.hpp"

namespace delivery::core::domain::order {

[[nodiscard]] auto MockOrder() -> MutableSharedRef<Order>;

} // namespace delivery::core::domain::order
