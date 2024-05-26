#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>

#include <core/ports/icourier_repository.hpp>

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] userver::utils::SharedRef<const core::ports::ICourierRepository>
    MakeCourierRepository(userver::storages::postgres::ClusterPtr);

}  // namespace delivery::infrastructure::adapters::postgres
