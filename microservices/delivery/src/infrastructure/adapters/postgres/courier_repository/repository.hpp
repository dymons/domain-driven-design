#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>

#include <core/ports/courier_repository/fwd.hpp>
#include <utils/memory.hpp>

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeCourierRepository(
    userver::storages::postgres::ClusterPtr)
    -> SharedRef<core::ports::ICourierRepository>;

[[nodiscard]] auto MakeCourierRepository(
    SharedRef<userver::storages::postgres::Transaction>)
    -> SharedRef<core::ports::ICourierRepository>;

}  // namespace delivery::infrastructure::adapters::postgres
