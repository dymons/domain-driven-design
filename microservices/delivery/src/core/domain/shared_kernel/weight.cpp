#include "weight.hpp"

#include "exceptions.hpp"

namespace delivery::core::domain::shared_kernel {

auto Weight::Create(int const value) -> Weight {
  if (value <= 0) {
    throw ArgumentException{"The weight must be a positive value"};
  }

  return Weight{value};
}

}  // namespace delivery::core::domain::shared_kernel
