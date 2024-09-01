#include "query_execution.hpp"

namespace delivery::infrastructure::adapters::postgres {

QueryExecution::QueryExecution(Cluster cluster)
    : executor_{std::move(cluster)} {}

QueryExecution::QueryExecution(Trx transaction)
    : executor_{std::move(transaction)} {}

}  // namespace delivery::infrastructure::adapters::postgres
