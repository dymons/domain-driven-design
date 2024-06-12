#pragma once

#include <userver/utils/not_null.hpp>

#include "idispatch_service.hpp"

namespace delivery::core::domain_services {

[[nodiscard]] auto MakeDispatchService()
    -> userver::utils::SharedRef<const IDispatchService>;

}  // namespace delivery::core::domain_services
