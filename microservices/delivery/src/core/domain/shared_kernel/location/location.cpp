#include "location.hpp"

#include <cmath>

#include <fmt/format.h>

#include <userver/utils/exception.hpp>

#include <core/domain/shared_kernel/exceptions.hpp>

namespace delivery::core::domain {

const auto kMinX = XCoord{1};
const auto kMaxX = XCoord{10};
const auto kMinY = YCoord{1};
const auto kMaxY = YCoord{10};

const Location Location::kMinLocation = Location{kMinX, kMinY};
const Location Location::kMaxLocation = Location{kMaxX, kMaxY};

Location::Location(XCoord x, YCoord y) {
  if (x < kMinX || x > kMaxX) {
    userver::utils::LogErrorAndThrow<ArgumentException>(fmt::format(
        "The coordinate x should be in range from {} to {}", kMinX, kMaxX));
  }

  if (y < kMinY || y > kMaxY) {
    userver::utils::LogErrorAndThrow<ArgumentException>(fmt::format(
        "The coordinate y should be in range from {} to {}", kMinY, kMaxY));
  }

  x_ = x.GetUnderlying();
  y_ = y.GetUnderlying();
}

auto Location::GetX() const noexcept -> XCoord { return XCoord{x_}; }

auto Location::GetY() const noexcept -> YCoord { return YCoord{y_}; }

auto Location::DistanceTo(Location const& other) const noexcept -> Distance {
  return Distance{
      std::abs(GetX().GetUnderlying() - other.GetX().GetUnderlying()) +
      std::abs(GetY().GetUnderlying() - other.GetY().GetUnderlying())};
}

}  // namespace delivery::core::domain
