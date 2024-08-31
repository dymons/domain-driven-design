#pragma once

#include <core/ports/order_repository/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::application::use_cases::commands::create_order {

[[nodiscard]] auto MakeCreateOrderHandler(
    SharedRef<core::ports::IOrderRepository>) -> SharedRef<ICreateOrderHandler>;

}  // namespace delivery::core::application::use_cases::commands::create_order
