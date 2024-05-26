#include "location.hpp"

#include <cmath>

#include <fmt/format.h>

#include "exceptions.hpp"

namespace delivery::core::domain::shared_kernel {

const Location Location::kMinLocation = Location{X{1}, Y{1}};
const Location Location::kMaxLocation = Location{X{10}, Y{10}};

auto Location::Create(X const x, Y const y) -> Location {
  if (x < kMinLocation.GetX() || x > kMaxLocation.GetX()) {
    throw ArgumentException{
        fmt::format("The coordinate x should be in range from {} to {}",
                    kMinLocation.GetX().GetUnderlying(),
                    kMaxLocation.GetX().GetUnderlying())};
  }
  if (y < kMinLocation.GetY() || y > kMaxLocation.GetY()) {
    throw ArgumentException{
        fmt::format("The coordinate y should be in range from {} to {}",
                    kMinLocation.GetY().GetUnderlying(),
                    kMaxLocation.GetY().GetUnderlying())};
  }
  return Location{x, y};
}

auto Location::DistanceTo(Location const& other) const noexcept -> Distance {
  return Distance{
      std::abs(GetX().GetUnderlying() - other.GetX().GetUnderlying()) +
      std::abs(GetY().GetUnderlying() - other.GetY().GetUnderlying())};
}

}  // namespace delivery::core::domain::shared_kernel
