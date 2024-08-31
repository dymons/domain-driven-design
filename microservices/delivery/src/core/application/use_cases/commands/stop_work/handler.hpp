#pragma once

#include <utils/memory.hpp>

#include <core/ports/courier_repository/fwd.hpp>

#include "fwd.hpp"

namespace delivery::core::application::use_cases::commands::stop_work {

[[nodiscard]] auto MakeStopWorkHandler(
    SharedRef<core::ports::ICourierRepository>) -> SharedRef<IStopWorkHandler>;

}  // namespace delivery::core::application::use_cases::commands::stop_work
