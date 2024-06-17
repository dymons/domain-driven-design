#pragma once

#include <utils/memory.hpp>

#include "iservice.hpp"

namespace delivery::core::domain_services {

[[nodiscard]] auto MockDispatchService(IDispatchService::DispatchResult)
    -> SharedRef<IDispatchService>;

}  // namespace delivery::core::domain_services
