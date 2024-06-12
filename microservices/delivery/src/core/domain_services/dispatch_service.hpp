#pragma once

#include <userver/utils/not_null.hpp>

namespace delivery::core::domain_services {

class IDispatchService;

[[nodiscard]] auto MakeDispatchService()
    -> userver::utils::SharedRef<const IDispatchService>;

}  // namespace delivery::core::domain_services
