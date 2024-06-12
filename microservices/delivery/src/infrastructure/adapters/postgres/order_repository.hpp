#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>
#include <userver/utils/not_null.hpp>

namespace delivery::core::ports {
class IOrderRepository;
}  // namespace delivery::core::ports

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeOrderRepository(userver::storages::postgres::ClusterPtr)
    -> userver::utils::SharedRef<const core::ports::IOrderRepository>;

}  // namespace delivery::infrastructure::adapters::postgres
