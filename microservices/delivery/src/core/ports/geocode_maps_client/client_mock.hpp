#pragma once

#include <core/domain/shared_kernel/location/location.hpp>

#include "iclient.hpp"

namespace delivery::core::ports {

[[nodiscard]] auto MockGeocodeMapsClient(
    core::domain::Location location = core::domain::Location::kMinLocation)
    -> SharedRef<IGeocodeMapsClient>;

}  // namespace delivery::core::ports
