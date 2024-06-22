#pragma once

#include <string>
#include <variant>
#include <vector>

namespace delivery::core::application::use_cases::queries::get_couriers {

class Location final {
  int x_;
  int y_;

 public:
  Location(int x, int y);

  [[nodiscard]] auto GetX() const noexcept -> int;
  [[nodiscard]] auto GetY() const noexcept -> int;
};

class Courier final {
  std::string id_;
  std::string name_;
  Location location_;

 public:
  Courier(std::string id, std::string name, Location location);

  [[nodiscard]] auto GetId() const noexcept -> std::string;
  [[nodiscard]] auto GetName() const noexcept -> std::string;
  [[nodiscard]] auto GetLocation() const noexcept -> Location;
};

struct Response200 final {
  std::vector<Courier> couriers;
};

using Response = std::variant<Response200>;

}  // namespace delivery::core::application::use_cases::queries::get_couriers
