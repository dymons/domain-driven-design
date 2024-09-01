#pragma once

#include <variant>

#include <userver/storages/postgres/cluster.hpp>

#include <utils/memory.hpp>
#include <utils/variant.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

class QueryExecution final {
 public:
  using Cluster = userver::storages::postgres::ClusterPtr;
  using Trx = MutableSharedRef<userver::storages::postgres::Transaction>;

  explicit QueryExecution(Cluster);
  explicit QueryExecution(Trx);

  template <typename... Args>
  [[nodiscard]] auto Execute(
      const userver::storages::postgres::ClusterHostType cluster_type,
      const userver::storages::postgres::Query& query,
      const Args&... args) const -> userver::storages::postgres::ResultSet {
    return std::visit(variant::overloaded{[&](const Cluster& executor) {
                                            return executor->Execute(
                                                cluster_type, query, args...);
                                          },
                                          [&](const Trx& executor) {
                                            return executor->Execute(query,
                                                                     args...);
                                          }},
                      executor_);
  }

 private:
  std::variant<Cluster, Trx> executor_;
};

}  // namespace delivery::infrastructure::adapters::postgres
