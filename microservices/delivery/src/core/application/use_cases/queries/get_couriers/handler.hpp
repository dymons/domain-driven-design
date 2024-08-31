#pragma once

#include <core/ports/courier_repository/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::application::use_cases::queries::get_couriers {

[[nodiscard]] auto MakeGetCouriersHandler(
    SharedRef<core::ports::ICourierRepository>)
    -> SharedRef<IGetCouriersHandler>;

}  // namespace delivery::core::application::use_cases::queries::get_couriers
