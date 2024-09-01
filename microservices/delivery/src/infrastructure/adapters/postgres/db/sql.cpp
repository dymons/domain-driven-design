#include "sql.hpp"

namespace delivery::infrastructure::adapters::postgres::sql {

const std::string kAddOrder = R"~(
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

const std::string kUpdateOrder = R"~(
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

}  // namespace delivery::infrastructure::adapters::postgres::sql
