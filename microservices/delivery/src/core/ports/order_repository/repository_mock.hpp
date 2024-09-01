#pragma once

#include <vector>

#include <core/domain/order/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::ports {

[[nodiscard]] auto MockOrderRepository(
    std::vector<MutableSharedRef<domain::order::Order>> = {})
    -> SharedRef<IOrderRepository>;

}  // namespace delivery::core::ports
