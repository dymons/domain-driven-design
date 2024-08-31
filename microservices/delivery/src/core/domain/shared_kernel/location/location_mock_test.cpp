#include "location_mock_test.hpp"

namespace delivery::core::domain {

auto MockLocation(int x, int y) -> Location { return {XCoord{x}, YCoord{y}}; }

}  // namespace delivery::core::domain
