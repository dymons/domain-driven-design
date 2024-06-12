#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>

#include <utils/memory.hpp>

namespace delivery::core::ports {
class IOrderRepository;
}  // namespace delivery::core::ports

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeOrderRepository(userver::storages::postgres::ClusterPtr)
    -> SharedRef<core::ports::IOrderRepository>;

}  // namespace delivery::infrastructure::adapters::postgres
