#include "sql.hpp"

namespace delivery::infrastructure::adapters::postgres::sql {

const std::string kAddOrder = R"~(
  INSERT INTO delivery.orders
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

}  // namespace delivery::infrastructure::adapters::postgres::sql
