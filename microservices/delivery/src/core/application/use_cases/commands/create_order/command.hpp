#pragma once

#include <string>

namespace delivery::application::use_cases::commands::create_order {

struct Command final {
  std::string basket_id{};
  std::string address{};
  int weight{};
};

}  // namespace delivery::application::use_cases::commands::create_order
