#pragma once

#include <utils/memory.hpp>

#include "ihandler.hpp"

namespace delivery::core::ports {
class IOrderRepository;
}  // namespace delivery::core::ports

namespace delivery::core::application::use_cases::queries::get_orders {

[[nodiscard]] auto MakeGetOrdersHandler(
    SharedRef<core::ports::IOrderRepository>) -> SharedRef<IGetOrdersHandler>;

}  // namespace delivery::core::application::use_cases::queries::get_orders
