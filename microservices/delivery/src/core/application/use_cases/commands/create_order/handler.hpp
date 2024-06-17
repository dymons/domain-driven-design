#pragma once

#include <utils/memory.hpp>

#include "ihandler.hpp"

namespace delivery::core::ports {
class IOrderRepository;
}  // namespace delivery::core::ports

namespace delivery::core::application::use_cases::commands::create_order {

[[nodiscard]] auto MakeCreateOrderHandler(
    SharedRef<core::ports::IOrderRepository>) -> SharedRef<ICreateOrderHandler>;

}  // namespace delivery::core::application::use_cases::commands::create_order
