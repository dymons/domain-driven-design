#include "location_mock_test.hpp"

namespace delivery::core::domain {

auto MockLocation(int x, int y) -> Location { return {X{x}, Y{y}}; }

}  // namespace delivery::core::domain
