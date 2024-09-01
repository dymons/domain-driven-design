#pragma once

#include <variant>

#include <userver/storages/postgres/cluster.hpp>

#include <utils/memory.hpp>
#include <utils/variant.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

class QueryExecution final {
  using Cluster = userver::storages::postgres::ClusterPtr;
  using Trx = MutableSharedRef<userver::storages::postgres::Transaction>;

 public:
  explicit QueryExecution(Cluster);
  explicit QueryExecution(Trx);

  template <typename... Args>
  [[nodiscard]] auto Execute(
      const userver::storages::postgres::ClusterHostType cluster_type,
      const userver::storages::postgres::Query& query,
      const Args&... args) const -> userver::storages::postgres::ResultSet;

 private:
  std::variant<Cluster, Trx> executor_;
};

}  // namespace delivery::infrastructure::adapters::postgres

#define DELIVERY_QUERY_EXECUTION_HPP
#include <infrastructure/adapters/postgres/query_execution/query_execution-inl.hpp>
#undef DELIVERY_QUERY_EXECUTION_HPP
