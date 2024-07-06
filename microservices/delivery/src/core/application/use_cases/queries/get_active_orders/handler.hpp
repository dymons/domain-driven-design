#pragma once

#include <utils/memory.hpp>

#include "ihandler.hpp"

namespace delivery::core::ports {
class IOrderRepository;
}  // namespace delivery::core::ports

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

[[nodiscard]] auto MakeGetActiveOrdersHandler(
    SharedRef<core::ports::IOrderRepository>)
    -> SharedRef<IGetActiveOrdersHandler>;

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
