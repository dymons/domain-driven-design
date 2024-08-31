#pragma once

#include <compare>

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain {

using XCoord = userver::utils::StrongTypedef<struct XCoordTag, int>;
using YCoord = userver::utils::StrongTypedef<struct YCoordTag, int>;
using Distance = userver::utils::StrongTypedef<struct DistanceTag, int>;

class Location final {
  int x_;
  int y_;

 public:
  static const Location kMinLocation;
  static const Location kMaxLocation;

  // Constructors

  Location(XCoord, YCoord);

  // Observers

  [[nodiscard]] auto GetX() const noexcept -> XCoord;
  [[nodiscard]] auto GetY() const noexcept -> YCoord;
  [[nodiscard]] auto DistanceTo(Location const&) const noexcept -> Distance;

  auto operator<=>(Location const&) const -> std::strong_ordering = default;
};

}  // namespace delivery::core::domain
