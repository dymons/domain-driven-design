#include "location.hpp"

#include <core/domain/shared_kernel/location.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(core::domain::shared_kernel::Location const& loc) -> Location {
  return {
      .x = loc.GetX().GetUnderlying(),
      .y = loc.GetY().GetUnderlying(),
  };
}

auto Convert(Location const& loc) -> core::domain::shared_kernel::Location {
  return core::domain::shared_kernel::Location::Create(
      core::domain::shared_kernel::X{loc.x},
      core::domain::shared_kernel::Y{loc.y});
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
