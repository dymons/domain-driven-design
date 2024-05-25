#pragma once

#include <stdexcept>

namespace delivery::core::domain::courier {

struct ArgumentException : std::invalid_argument {
  using std::invalid_argument::invalid_argument;
};

struct IllegalStateException : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct TryStopWorkingWithIncompleteDelivery final : IllegalStateException {
  using IllegalStateException::IllegalStateException;
};

struct TryStartWorkingWhenAlreadyStarted final : IllegalStateException {
  using IllegalStateException::IllegalStateException;
};

struct TryAssignOrderWhenNotAvailable final : IllegalStateException {
  using IllegalStateException::IllegalStateException;
};

struct TryAssignOrderWhenCourierHasAlreadyBusy final : IllegalStateException {
  using IllegalStateException::IllegalStateException;
};

}  // namespace delivery::core::domain::courier
