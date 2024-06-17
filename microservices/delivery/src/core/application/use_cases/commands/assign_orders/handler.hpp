#pragma once

#include <utils/memory.hpp>

#include "ihandler.hpp"

namespace delivery::core::ports {
class IOrderRepository;
}  // namespace delivery::core::ports

namespace delivery::core::ports {
class ICourierRepository;
}  // namespace delivery::core::ports

namespace delivery::core::domain_services {
class IDispatchService;
}  // namespace delivery::core::domain_services

namespace delivery::core::application::use_cases::commands::assign_orders {

[[nodiscard]] auto MakeAssignOrdersHandler(
    SharedRef<core::ports::ICourierRepository>,
    SharedRef<core::ports::IOrderRepository>,
    SharedRef<core::domain_services::IDispatchService>)
    -> SharedRef<IAssignOrdersHandler>;

}  // namespace delivery::core::application::use_cases::commands::assign_orders
