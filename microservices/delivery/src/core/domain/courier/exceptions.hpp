#pragma once

#include <stdexcept>

namespace delivery::core::domain::courier {

struct ArgumentException : std::invalid_argument {
  using std::invalid_argument::invalid_argument;
};

struct IllegalStateException : std::runtime_error {
  using std::runtime_error::runtime_error;
};

} // namespace delivery::core::domain::courier
