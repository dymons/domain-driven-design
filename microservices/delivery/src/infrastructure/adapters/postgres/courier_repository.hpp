#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>
#include <userver/utils/not_null.hpp>

namespace delivery::core::ports {
class ICourierRepository;
}  // namespace delivery::core::ports

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeCourierRepository(
    userver::storages::postgres::ClusterPtr)
    -> userver::utils::SharedRef<const core::ports::ICourierRepository>;

}  // namespace delivery::infrastructure::adapters::postgres
