#pragma once

#include <stdexcept>

namespace delivery::core::domain {

struct ArgumentException : std::invalid_argument {
  using std::invalid_argument::invalid_argument;
};

}  // namespace delivery::core::domain
