#include "courier.hpp"

#include <core/domain/courier/courier.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(core::domain::courier::Courier const& courier) -> Courier {
  return {
      .id = courier.GetId().GetUnderlying(),
      .name = courier.GetName().GetUnderlying(),
      .status = ToString(courier.GetStatus()),
      .transport = dto::Convert(courier.GetTransport()),
      .current_location = dto::Convert(courier.GetCurrentLocation()),
  };
}

auto Convert(Courier const& courier) -> core::domain::courier::Courier {
  return core::domain::courier::Courier::Hydrate(
      core::domain::courier::CourierId{courier.id},
      core::domain::courier::CourierName{courier.name},
      dto::Convert(courier.transport), dto::Convert(courier.current_location),
      core::domain::courier::FromString(courier.status));
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
