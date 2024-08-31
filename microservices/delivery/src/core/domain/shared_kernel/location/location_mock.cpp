#include "location_mock.hpp"

namespace delivery::core::domain {

auto MockLocation(int x, int y) -> Location { return {XCoord{x}, YCoord{y}}; }

}  // namespace delivery::core::domain
