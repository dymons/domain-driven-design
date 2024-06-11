#pragma once

#include <compare>

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain {

using X = userver::utils::StrongTypedef<struct XTag, int>;
using Y = userver::utils::StrongTypedef<struct YTag, int>;
using Distance = userver::utils::StrongTypedef<struct DistanceTag, int>;

class Location {
  int x_;
  int y_;

 public:
  static const Location kMinLocation;
  static const Location kMaxLocation;

  // Constructors

  Location(X, Y);

  // Observers

  [[nodiscard]] auto GetX() const noexcept -> X;
  [[nodiscard]] auto GetY() const noexcept -> Y;
  [[nodiscard]] auto DistanceTo(Location const&) const noexcept -> Distance;

  auto operator<=>(Location const&) const -> std::strong_ordering = default;
};

}  // namespace delivery::core::domain
