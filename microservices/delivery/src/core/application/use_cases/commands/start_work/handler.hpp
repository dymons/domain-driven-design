#pragma once

#include <utils/memory.hpp>

#include "ihandler.hpp"

namespace delivery::core::ports {
class ICourierRepository;
}  // namespace delivery::core::ports

namespace delivery::core::application::use_cases::commands::start_work {

[[nodiscard]] auto MakeStartWorkHandler(
    SharedRef<core::ports::ICourierRepository>) -> SharedRef<IStartWorkHandler>;

}  // namespace delivery::core::application::use_cases::commands::start_work
