#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>

#include <core/ports/unit_of_work/fwd.hpp>
#include <utils/memory.hpp>

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeUnitOfWork(userver::storages::postgres::ClusterPtr)
    -> SharedRef<core::ports::IUnitOfWork>;

}  // namespace delivery::infrastructure::adapters::postgres
