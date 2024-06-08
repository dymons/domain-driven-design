#pragma once

#include <core/domain/shared_kernel/location.hpp>
#include "exceptions.hpp"
#include "status.hpp"
#include "strong_typedefs.hpp"
#include "transport.hpp"

namespace delivery::core::domain::courier {

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

  [[nodiscard]] static auto Hydrate(CourierId id, CourierName name,
                                    Transport transport,
                                    shared_kernel::Location current_location,
                                    CourierStatus status) -> Courier;

  // Observers

  auto GetId() const noexcept -> CourierId;
  auto GetName() const noexcept -> CourierName;
  auto GetTransport() const noexcept -> Transport;
  auto GetCurrentLocation() const noexcept -> shared_kernel::Location;
  auto GetStatus() const noexcept -> CourierStatus;
  auto CalculateTimeToPoint(shared_kernel::Location) const noexcept -> Time;

  // Modifiers

  auto MoveTo(shared_kernel::Location location) -> void;
  auto StartWork() -> void;
  auto StopWork() -> void;
  auto InWork() -> void;
};

}  // namespace delivery::core::domain::courier
