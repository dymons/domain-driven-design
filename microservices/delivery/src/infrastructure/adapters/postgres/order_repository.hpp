#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>
#include <userver/utils/not_null.hpp>

#include <core/ports/iorder_repository.hpp>

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] userver::utils::SharedRef<const core::ports::IOrderRepository>
    MakeOrderRepository(userver::storages::postgres::ClusterPtr);

}  // namespace delivery::infrastructure::adapters::postgres
