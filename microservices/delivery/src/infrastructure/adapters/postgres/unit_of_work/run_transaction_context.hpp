#pragma once

#include <userver/storages/postgres/postgres_fwd.hpp>

#include <utils/memory.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

[[nodiscard]] auto MakeRunTransactionContext(
    MutableSharedRef<userver::storages::postgres::Transaction>)
    -> SharedRef<IRunTransactionContext>;

}  // namespace delivery::infrastructure::adapters::postgres
