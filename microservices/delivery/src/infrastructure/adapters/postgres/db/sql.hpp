#pragma once

#include <userver/storages/postgres/query.hpp>

namespace delivery::infrastructure::adapters::postgres::sql {

extern const userver::storages::postgres::Query kAddOrder;
extern const userver::storages::postgres::Query kUpdateOrder;
extern const userver::storages::postgres::Query kGetOrderById;
extern const userver::storages::postgres::Query kGetOrdersExcludeByStatus;
extern const userver::storages::postgres::Query kGetOrdersByStatus;
extern const userver::storages::postgres::Query kGetOrders;

extern const userver::storages::postgres::Query kAddCourier;
extern const userver::storages::postgres::Query kUpdateCourier;
extern const userver::storages::postgres::Query kGetCourierById;
extern const userver::storages::postgres::Query kGetCouriers;
extern const userver::storages::postgres::Query kGetCouriersByStatus;

}  // namespace delivery::infrastructure::adapters::postgres::sql
