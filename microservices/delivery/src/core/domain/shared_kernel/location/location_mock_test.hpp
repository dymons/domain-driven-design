#pragma once

#include "location.hpp"

namespace delivery::core::domain {

[[nodiscard]] auto MockLocation(int x = 5, int y = 5) -> Location;

} // namespace delivery::core::domain
