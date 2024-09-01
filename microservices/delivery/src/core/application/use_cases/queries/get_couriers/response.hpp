#pragma once

#include <string>
#include <variant>
#include <vector>

namespace delivery::core::application::use_cases::queries::get_couriers {

struct Location final {
  int x;
  int y;
};

struct Courier final {
  std::string id;
  std::string name;
  Location location;
};

}  // namespace delivery::core::application::use_cases::queries::get_couriers
