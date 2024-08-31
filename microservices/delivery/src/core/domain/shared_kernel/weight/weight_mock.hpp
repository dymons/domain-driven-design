#pragma once

#include "weight.hpp"

namespace delivery::core::domain {

[[nodiscard]] auto MockWeight(int value = 5) -> Weight;

}  // namespace delivery::core::domain
