#pragma once

#include <unordered_set>

#include <core/domain/courier/fwd.hpp>
#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::core::ports {

[[nodiscard]] auto MockCourierRepository(
    std::unordered_set<MutableSharedRef<domain::courier::Courier>> = {})
    -> SharedRef<ICourierRepository>;

}  // namespace delivery::core::ports
