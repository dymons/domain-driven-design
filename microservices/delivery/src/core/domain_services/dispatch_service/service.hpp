#pragma once

#include <utils/memory.hpp>

namespace delivery::core::domain_services {

class IDispatchService;

[[nodiscard]] auto MakeDispatchService() -> SharedRef<IDispatchService>;

}  // namespace delivery::core::domain_services
