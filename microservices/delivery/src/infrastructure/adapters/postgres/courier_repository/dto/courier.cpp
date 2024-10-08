#include "courier.hpp"

#include <core/domain/courier/courier.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

auto Convert(SharedRef<core::domain::courier::Courier> const& courier)
    -> Courier {
  return {
      .id = courier->GetId(),
      .name = courier->GetName(),
      .status = courier->GetStatus().ToString(),
      .transport = dto::Convert(courier->GetTransport()),
      .current_location = dto::Convert(courier->GetCurrentLocation()),
  };
}

auto Convert(Courier const& courier)
    -> MutableSharedRef<core::domain::courier::Courier> {
  return core::domain::courier::Courier::Hydrate(
      core::domain::CourierId{courier.id},
      core::domain::courier::CourierName{courier.name},
      dto::Convert(courier.transport), dto::Convert(courier.current_location),
      core::domain::courier::CourierStatus::FromString(courier.status));
}

auto Convert(Courier&& courier)
    -> MutableSharedRef<core::domain::courier::Courier> {
  return core::domain::courier::Courier::Hydrate(
      core::domain::CourierId{std::move(courier.id)},
      core::domain::courier::CourierName{std::move(courier.name)},
      dto::Convert(std::move(courier.transport)),
      dto::Convert(courier.current_location),
      core::domain::courier::CourierStatus::FromString(
          std::move(courier.status)));
}

}  // namespace delivery::infrastructure::adapters::postgres::dto
