#pragma once

#include <string>
#include <variant>
#include <vector>

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

  auto operator<=>(Location const&) const -> std::strong_ordering = default;
};

class Order final {
  std::string id_;
  Location location_;

 public:
  Order(std::string id, Location location);

  [[nodiscard]] auto GetId() const noexcept -> std::string;
  [[nodiscard]] auto GetLocation() const noexcept -> Location;

  auto operator<=>(Order const&) const -> std::strong_ordering = default;
};

struct Response200 {
  std::vector<Order> orders;
};

using Response = std::variant<Response200>;

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
