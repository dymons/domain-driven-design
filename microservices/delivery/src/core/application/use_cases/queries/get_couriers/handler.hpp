#pragma once

#include <utils/memory.hpp>

#include "ihandler.hpp"

namespace delivery::core::ports {
class ICourierRepository;
}  // namespace delivery::core::ports

namespace delivery::core::application::use_cases::queries::get_couriers {

[[nodiscard]] auto MakeGetCouriersHandler(
    SharedRef<core::ports::ICourierRepository>)
    -> SharedRef<IGetCouriersHandler>;

}  // namespace delivery::core::application::use_cases::queries::get_couriers
