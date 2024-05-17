#include "location.hpp"

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

}  // namespace delivery::core::domain::shared_kernel
