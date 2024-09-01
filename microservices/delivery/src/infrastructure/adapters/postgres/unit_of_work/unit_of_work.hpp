#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>

#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeUnitOfWork(userver::storages::postgres::ClusterPtr)
    -> SharedRef<IUnitOfWork>;

}  // namespace delivery::infrastructure::adapters::postgres
