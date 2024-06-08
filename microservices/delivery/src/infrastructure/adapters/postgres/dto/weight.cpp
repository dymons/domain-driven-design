#include "weight.hpp"

#include <core/domain/shared_kernel/weight.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(core::domain::Weight const& weight) -> Weight {
  return {.value = weight.GetWeight()};
}

auto Convert(Weight const& weight) -> core::domain::Weight {
  return core::domain::Weight{weight.value};
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
