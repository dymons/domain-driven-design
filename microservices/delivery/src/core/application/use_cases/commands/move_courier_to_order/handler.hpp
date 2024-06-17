#pragma once

#include <utils/memory.hpp>

#include "ihandler.hpp"

namespace delivery::core::ports {
class IOrderRepository;
}  // namespace delivery::core::ports

namespace delivery::core::ports {
class ICourierRepository;
}  // namespace delivery::core::ports

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
