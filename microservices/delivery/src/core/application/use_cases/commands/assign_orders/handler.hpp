#pragma once

#include <core/domain_services/dispatch_service/fwd.hpp>
#include <core/ports/courier_repository/fwd.hpp>
#include <core/ports/order_repository/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::application::use_cases::commands::assign_orders {

[[nodiscard]] auto MakeAssignOrdersHandler(
    SharedRef<core::ports::ICourierRepository>,
    SharedRef<core::ports::IOrderRepository>,
    SharedRef<core::domain_services::IDispatchService>)
    -> SharedRef<IAssignOrdersHandler>;

}  // namespace delivery::core::application::use_cases::commands::assign_orders
