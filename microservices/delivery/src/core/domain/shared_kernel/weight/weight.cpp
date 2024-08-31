#include "weight.hpp"

#include <userver/utils/exception.hpp>

#include <core/domain/shared_kernel/exceptions.hpp>

namespace delivery::core::domain {

Weight::Weight(int const value) {
  if (value <= 0) {
    userver::utils::LogErrorAndThrow<ArgumentException>(
        "The weight must be a positive value");
  }

  value_ = value;
}

auto Weight::GetWeight() const noexcept -> int { return value_; }

}  // namespace delivery::core::domain
