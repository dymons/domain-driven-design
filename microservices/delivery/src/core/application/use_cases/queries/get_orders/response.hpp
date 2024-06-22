#pragma once

#include <string>
#include <variant>
#include <vector>

namespace delivery::core::application::use_cases::queries::get_orders {

class Location final {
  int x_;
  int y_;

 public:
  Location(int x, int y);

  [[nodiscard]] auto GetX() const noexcept -> int;
  [[nodiscard]] auto GetY() const noexcept -> int;
};

class Order final {
  std::string id_;
  Location location_;

 public:
  Order(std::string id, Location location);

  [[nodiscard]] auto GetId() const noexcept -> std::string;
  [[nodiscard]] auto GetLocation() const noexcept -> Location;
};

struct Response200 {
  std::vector<Order> orders;
};

using Response = std::variant<Response200>;

}  // namespace delivery::core::application::use_cases::queries::get_orders
