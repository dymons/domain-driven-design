#pragma once

#include <vector>

#include <core/domain/courier/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::ports {

[[nodiscard]] auto MockCourierRepository(
    std::vector<MutableSharedRef<domain::courier::Courier>> = {})
    -> SharedRef<ICourierRepository>;

}  // namespace delivery::core::ports
