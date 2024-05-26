#pragma once

#include <compare>

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain::shared_kernel {

using X = userver::utils::StrongTypedef<struct XTag, int>;
using Y = userver::utils::StrongTypedef<struct YTag, int>;
using Distance = userver::utils::StrongTypedef<struct DistanceTag, int>;

class Location {
  int x_;
  int y_;

  // Constructors

  Location(X x, Y y) : x_(x.GetUnderlying()), y_(y.GetUnderlying()) {}

 public:
  static const Location kMinLocation;
  static const Location kMaxLocation;

  [[nodiscard]] static auto Create(X x, Y y) -> Location;

  // Observers

  auto GetX() const noexcept -> X;
  auto GetY() const noexcept -> Y;
  auto DistanceTo(Location const&) const noexcept -> Distance;

  auto operator<=>(Location const&) const -> std::strong_ordering = default;
};

}  // namespace delivery::core::domain::shared_kernel
