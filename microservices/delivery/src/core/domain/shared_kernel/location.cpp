#include "location.hpp"

#include <cmath>

#include "exceptions.hpp"

namespace delivery::core::domain::shared_kernel {

namespace {

void ValidateCoordinate(int const coord) {
  if (coord < 1 || coord > 10) {
    throw ArgumentException{"The coordinate should be in range from 1 to 10"};
  }
}

}  // namespace

auto Location::Create(int const x, int const y) -> Location {
  ValidateCoordinate(x);
  ValidateCoordinate(y);
  return Location{x, y};
}

auto Location::DistanceTo(Location const& other) const noexcept -> int {
  return std::abs(GetX() - other.GetX()) + std::abs(GetY() - other.GetY());
}

}  // namespace delivery::core::domain::shared_kernel
