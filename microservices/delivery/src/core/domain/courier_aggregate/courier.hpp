#pragma once

#include <core/domain/shared_kernel/location.hpp>
#include <utility>
#include "courier_status.hpp"
#include "exceptions.hpp"
#include "strong_typedefs.hpp"
#include "transport.hpp"

namespace delivery::core::domain::courier_aggregate {

struct TryAssignOrderWhenNotAvailable final : IllegalStateException {
  TryAssignOrderWhenNotAvailable() : IllegalStateException{""} {}
  auto what() const noexcept -> const char* final {
    return "You cannot take an order to work if the courier has not started "
           "the working day";
  }
};

struct TryAssignOrderWhenCourierHasAlreadyBusy final : IllegalStateException {
  TryAssignOrderWhenCourierHasAlreadyBusy() : IllegalStateException{""} {}
  auto what() const noexcept -> const char* final {
    return "You can't take an order to work if the courier is already busy";
  }
};

class Courier {
  CourierId id_;
  CourierName name_;
  Transport transport_;
  shared_kernel::Location current_location_;
  CourierStatus status_;

  // Constructors

  Courier(CourierId id, CourierName name, Transport transport,
          shared_kernel::Location current_location, CourierStatus status)
      : id_(std::move(id)),
        name_(std::move(name)),
        transport_(std::move(transport)),
        current_location_(current_location),
        status_(status) {}

 public:
  [[nodiscard]] static auto Create(CourierName name,
                                   Transport transport) -> Courier;

  // Observers

  auto GetId() const -> CourierId;
  auto GetName() const -> CourierName;
  auto GetTransport() const -> Transport;
  auto GetCurrentLocation() const -> shared_kernel::Location;
  auto GetStatus() const -> CourierStatus;

  // Modifiers

  auto MoveTo(shared_kernel::Location location) -> void;
  auto StartWork() -> void;
  auto StopWork() -> void;
  auto InWork() -> void;
  auto CalculateTimeToPoint(shared_kernel::Location location) -> void;
};

}  // namespace delivery::core::domain::courier_aggregate
