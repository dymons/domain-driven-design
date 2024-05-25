#pragma once

#include <stdexcept>

namespace delivery::core::domain::order {

struct ArgumentException : std::invalid_argument {
  using std::invalid_argument::invalid_argument;
};

struct IllegalStateException : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct CantCompletedNotAssignedOrder final : IllegalStateException {
  using IllegalStateException::IllegalStateException;
};

struct CantAssignOrderToBusyCourier final : IllegalStateException {
  using IllegalStateException::IllegalStateException;
};

}  // namespace delivery::core::domain::order
