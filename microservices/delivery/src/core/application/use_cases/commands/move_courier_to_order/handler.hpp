#pragma once

#include <core/ports/courier_repository/fwd.hpp>
#include <core/ports/order_repository/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

// clang-format off
namespace delivery::core::application::use_cases::commands::move_courier_to_order {
// clang-format on

[[nodiscard]] auto MakeMoveCourierToOrderHandler(
    SharedRef<core::ports::ICourierRepository>,
    SharedRef<core::ports::IOrderRepository>)
    -> SharedRef<IMoveCourierToOrderHandler>;

// clang-format off
}  // namespace delivery::core::application::use_cases::commands::move_courier_to_order
// clang-format on
