#include "weight.hpp"

#include "exceptions.hpp"

namespace delivery::core::domain {

Weight::Weight(int const value) : value_(value) {
  if (value <= 0) {
    throw ArgumentException{"The weight must be a positive value"};
  }
}

auto Weight::GetWeight() const noexcept -> int { return value_; }

}  // namespace delivery::core::domain
