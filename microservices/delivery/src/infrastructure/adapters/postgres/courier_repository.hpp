#pragma once

#include <core/ports/icourier_repository.hpp>

namespace delivery::infrastructure::adapters::postgres {

core::ports::ICourierRepositoryRef MakeCourierRepository();

}  // namespace delivery::infrastructure::adapters::postgres
