#pragma once

#include <string>

namespace delivery::infrastructure::adapters::postgres::sql {

extern const std::string kAddOrder;
extern const std::string kUpdateOrder;
extern const std::string kGetOrderById;
extern const std::string kGetOrdersExcludeByStatus;
extern const std::string kGetOrdersByStatus;
extern const std::string kGetOrders;

}  // namespace delivery::infrastructure::adapters::postgres::sql
