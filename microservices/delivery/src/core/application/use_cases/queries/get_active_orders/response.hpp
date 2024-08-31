#pragma once

#include <string>

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

class Location final {
  int x_;
  int y_;

 public:
  Location(int x, int y);

  [[nodiscard]] auto GetX() const noexcept -> int;
  [[nodiscard]] auto GetY() const noexcept -> int;

  auto operator<=>(Location const&) const = default;
};

class Order final {
  std::string id_;
  Location location_;

 public:
  Order(std::string id, Location location);

  [[nodiscard]] auto GetId() const noexcept -> std::string;
  [[nodiscard]] auto GetLocation() const noexcept -> Location;

  auto operator<=>(Order const&) const = default;
};

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
