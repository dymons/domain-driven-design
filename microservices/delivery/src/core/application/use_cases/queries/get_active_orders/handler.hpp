#pragma once

#include <core/ports/order_repository/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

[[nodiscard]] auto MakeGetActiveOrdersHandler(
    SharedRef<core::ports::IOrderRepository>)
    -> SharedRef<IGetActiveOrdersHandler>;

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
