#include "weight.hpp"

namespace delivery::core::domain::shared_kernel {

auto Weight::Create(int const weight) -> Weight { return Weight{weight}; }

}  // namespace delivery::core::domain::shared_kernel
