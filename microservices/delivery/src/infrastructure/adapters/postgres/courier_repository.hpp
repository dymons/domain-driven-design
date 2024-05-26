#pragma once

#include <core/ports/icourier_repository.hpp>

namespace delivery::infrastructure::adapters::postgres {

userver::utils::SharedRef<const core::ports::ICourierRepository>
MakeCourierRepository();

}  // namespace delivery::infrastructure::adapters::postgres
