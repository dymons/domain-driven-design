#pragma once

#include <unordered_set>

#include "irepository.hpp"

namespace delivery::core::ports {

[[nodiscard]] auto MockOrderRepository(
    std::unordered_set<MutableSharedRef<domain::order::Order>> = {})
    -> SharedRef<IOrderRepository>;

}  // namespace delivery::core::ports
