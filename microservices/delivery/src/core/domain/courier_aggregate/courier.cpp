#include "courier.hpp"

#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::courier_aggregate {

Courier Courier::Create(CourierName name, Transport transport) {
  return {
      CourierId{userver::utils::generators::GenerateUuidV7()}, std::move(name),
      transport,
      shared_kernel::Location::Create(shared_kernel::X{1}, shared_kernel::Y{1}),
      CourierStatus::NotAvailable};
}

auto Courier::GetId() const noexcept -> CourierId { return id_; }

auto Courier::GetName() const noexcept -> CourierName { return name_; }

auto Courier::GetTransport() const noexcept -> Transport { return transport_; }

auto Courier::GetCurrentLocation() const noexcept -> shared_kernel::Location {
  return current_location_;
}

auto Courier::GetCourierStatus() const noexcept -> CourierStatus {
  return status_;
}

}  // namespace delivery::core::domain::courier_aggregate
