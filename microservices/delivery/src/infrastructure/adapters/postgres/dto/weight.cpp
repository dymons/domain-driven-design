#include "weight.hpp"

#include <core/domain/shared_kernel/weight.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(core::domain::shared_kernel::Weight const& weight) -> Weight {
  return {.value = weight.GetWeight()};
}

auto Convert(Weight const& weight) -> core::domain::shared_kernel::Weight {
  return core::domain::shared_kernel::Weight{weight.value};
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
