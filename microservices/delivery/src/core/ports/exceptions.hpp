#pragma once

#include <stdexcept>

namespace delivery::core::ports {

struct CourierNotFound : std::runtime_error {
  using std::runtime_error::runtime_error;
};

} // namespace delivery::core::ports
