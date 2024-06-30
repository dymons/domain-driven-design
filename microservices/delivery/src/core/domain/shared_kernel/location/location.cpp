#include "location.hpp"

#include <cmath>

#include <fmt/format.h>

#include <userver/utils/exception.hpp>

#include <core/domain/shared_kernel/exceptions.hpp>

namespace delivery::core::domain {

const auto kMinX = X{1};
const auto kMaxX = X{10};
const auto kMinY = Y{1};
const auto kMaxY = Y{10};

const Location Location::kMinLocation = Location{kMinX, kMinY};
const Location Location::kMaxLocation = Location{kMaxX, kMaxY};

Location::Location(X x, Y y) {
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

auto Location::GetX() const noexcept -> X { return X{x_}; }

auto Location::GetY() const noexcept -> Y { return Y{y_}; }

auto Location::DistanceTo(Location const& other) const noexcept -> Distance {
  return Distance{
      std::abs(GetX().GetUnderlying() - other.GetX().GetUnderlying()) +
      std::abs(GetY().GetUnderlying() - other.GetY().GetUnderlying())};
}

}  // namespace delivery::core::domain
