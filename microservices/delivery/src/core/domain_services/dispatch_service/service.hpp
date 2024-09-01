#pragma once

#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::domain_services {

[[nodiscard]] auto MakeDispatchService() -> SharedRef<IDispatchService>;

}  // namespace delivery::core::domain_services
