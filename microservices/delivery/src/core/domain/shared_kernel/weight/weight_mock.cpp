#include "weight_mock.hpp"

namespace delivery::core::domain {

auto MockWeight(int value) -> Weight { return value; }

}  // namespace delivery::core::domain
