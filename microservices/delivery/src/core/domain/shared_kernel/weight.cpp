#include "weight.hpp"

#include "exceptions.hpp"

namespace delivery::core::domain::shared_kernel {

auto Weight::Create(int const weight) -> Weight {
  if (weight <= 0) {
    throw InvalidArgument{"The weight must be a positive value"};
  }

  return Weight{weight};
}

}  // namespace delivery::core::domain::shared_kernel
