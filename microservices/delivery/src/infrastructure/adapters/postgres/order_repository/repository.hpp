#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>

#include <core/ports/order_repository/fwd.hpp>
#include <utils/memory.hpp>

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeOrderRepository(userver::storages::postgres::ClusterPtr)
    -> SharedRef<core::ports::IOrderRepository>;

[[nodiscard]] auto MakeOrderRepository(
    MutableSharedRef<userver::storages::postgres::Transaction>)
    -> SharedRef<core::ports::IOrderRepository>;

}  // namespace delivery::infrastructure::adapters::postgres
