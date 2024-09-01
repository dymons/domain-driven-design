#ifndef DELIVERY_QUERY_EXECUTION_HPP
#error This file may only be included from query_execution.hpp
#endif

namespace delivery::infrastructure::adapters::postgres {

template <typename... Args>
auto QueryExecution::Execute(
    const userver::storages::postgres::ClusterHostType cluster_type,
    const userver::storages::postgres::Query& query, const Args&... args) const
    -> userver::storages::postgres::ResultSet {
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

}  // namespace delivery::infrastructure::adapters::postgres