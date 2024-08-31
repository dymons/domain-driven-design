#include "location.hpp"

#include <core/domain/shared_kernel/location/location.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(core::domain::Location const& loc) -> Location {
  return {
      .x = loc.GetX().GetUnderlying(),
      .y = loc.GetY().GetUnderlying(),
  };
}

auto Convert(Location const& loc) -> core::domain::Location {
  return core::domain::Location{core::domain::XCoord{loc.x},
                                core::domain::YCoord{loc.y}};
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
