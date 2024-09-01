#include "sql.hpp"

namespace delivery::infrastructure::adapters::postgres::sql {

const userver::storages::postgres::Query kAddOrder = R"~(
  INSERT INTO
    delivery.orders
  (
    id,
    status,
    courier_id,
    delivery_location,
    weight
  )
  VALUES
  (
    $1,
    $2,
    $3,
    ROW($4, $5),
    ROW($6)
  )
  ON CONFLICT (id) DO NOTHING
  RETURNING id
)~";

const userver::storages::postgres::Query kUpdateOrder = R"~(
  UPDATE
    delivery.orders
  SET
    id=$1,
    status=$2,
    courier_id=$3,
    delivery_location=$4,
    weight=$5
  WHERE
    id = $1
)~";

const userver::storages::postgres::Query kGetOrderById = R"~(
  SELECT
    id,
    status,
    courier_id,
    delivery_location,
    weight
  FROM
    delivery.orders
  WHERE
    id = $1
)~";

const userver::storages::postgres::Query kGetOrdersExcludeByStatus = R"~(
  SELECT
    id,
    status,
    courier_id,
    delivery_location,
    weight
  FROM
    delivery.orders
  WHERE
    status != $1
)~";

const userver::storages::postgres::Query kGetOrdersByStatus = R"~(
  SELECT
    id,
    status,
    courier_id,
    delivery_location,
    weight
  FROM
    delivery.orders
  WHERE
    status = $1
)~";

const userver::storages::postgres::Query kGetOrders = R"~(
  SELECT
    id,
    status,
    courier_id,
    delivery_location,
    weight
  FROM
    delivery.orders
)~";

const userver::storages::postgres::Query kAddCourier = R"~(
  INSERT INTO
    delivery.couriers
  (
    id,
    name,
    transport,
    current_location,
    status
  )
  VALUES
  (
    $1,
    $2,
    $3,
    $4,
    $5
  )
)~";

const userver::storages::postgres::Query kUpdateCourier = R"~(
  UPDATE
    delivery.couriers
  SET
    id=$1,
    name=$2,
    transport=$3,
    current_location=$4,
    status=$5
  WHERE
    id = $1
)~";

const userver::storages::postgres::Query kGetCourierById = R"~(
  SELECT
    id,
    name,
    transport,
    current_location,
    status
  FROM
    delivery.couriers
  WHERE
    id = $1
)~";

const userver::storages::postgres::Query kGetCouriers = R"~(
  SELECT
    id,
    name,
    status,
    transport,
    current_location
  FROM
    delivery.couriers
)~";

const userver::storages::postgres::Query kGetCouriersByStatus = R"~(
  SELECT
    id,
    name,
    status,
    transport,
    current_location
  FROM
    delivery.couriers
  WHERE
    status = $1
)~";

}  // namespace delivery::infrastructure::adapters::postgres::sql
