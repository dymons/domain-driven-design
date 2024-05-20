#include "courier.hpp"

#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::courier_aggregate {

Courier Courier::Create(CourierName courier_name, Transport transport) {
  return {
      CourierId{userver::utils::generators::GenerateUuidV7()},
      std::move(courier_name), transport,
      shared_kernel::Location::Create(shared_kernel::X{1}, shared_kernel::Y{1}),
      CourierStatus::NotAvailable};
}

}  // namespace delivery::core::domain::courier_aggregate
