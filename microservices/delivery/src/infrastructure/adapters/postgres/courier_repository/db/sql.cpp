#include "sql.hpp"

namespace delivery::infrastructure::adapters::postgres::sql {

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
