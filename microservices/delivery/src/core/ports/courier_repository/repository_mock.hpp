#pragma once

#include "irepository.hpp"

namespace delivery::core::ports {

[[nodiscard]] auto MockCourierRepository(
    std::unordered_set<MutableSharedRef<domain::courier::Courier>> = {})
    -> SharedRef<ICourierRepository>;

}  // namespace delivery::core::ports
