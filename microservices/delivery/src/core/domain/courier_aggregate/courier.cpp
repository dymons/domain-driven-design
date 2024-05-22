#include "courier.hpp"

#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::courier_aggregate {

auto Courier::Create(CourierName name, Transport transport) -> Courier {
  return {
      CourierId{userver::utils::generators::GenerateUuidV7()}, std::move(name),
      transport,
      shared_kernel::Location::Create(shared_kernel::X{1}, shared_kernel::Y{1}),
      CourierStatus::NotAvailable};
}

auto Courier::GetId() const -> CourierId { return id_; }

auto Courier::GetName() const -> CourierName { return name_; }

auto Courier::GetTransport() const -> Transport { return transport_; }

auto Courier::GetCurrentLocation() const -> shared_kernel::Location {
  return current_location_;
}

auto Courier::GetStatus() const -> CourierStatus { return status_; }

auto Courier::MoveTo(shared_kernel::Location const location) -> void {}

auto Courier::StartWork() -> void {
  if (status_ == CourierStatus::NotAvailable) {
    throw TryAssignOrderWhenNotAvailable{};
  }
  if (status_ == CourierStatus::Busy) {
    throw TryAssignOrderWhenCourierHasAlreadyBusy{};
  }

  status_ = CourierStatus::Busy;
}

auto Courier::StopWork() -> void {}

auto Courier::InWork() -> void {}

auto Courier::CalculateTimeToPoint(shared_kernel::Location location) -> void {

}

}  // namespace delivery::core::domain::courier_aggregate
