#pragma once

#include <string>

#include "location.hpp"
#include "transport.hpp"

namespace delivery::infrastructure::adapters::postgres::dto {

struct Courier final {
  std::string id;
  std::string name;
  std::string status;
  Transport transport;
  Location current_location;
};

}  // namespace delivery::infrastructure::adapters::postgres::dto
