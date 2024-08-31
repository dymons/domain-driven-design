#pragma once

#include <core/ports/courier_repository/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::application::use_cases::commands::start_work {

[[nodiscard]] auto MakeStartWorkHandler(
    SharedRef<core::ports::ICourierRepository>) -> SharedRef<IStartWorkHandler>;

}  // namespace delivery::core::application::use_cases::commands::start_work
