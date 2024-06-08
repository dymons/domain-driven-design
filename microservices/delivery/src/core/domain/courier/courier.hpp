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
  Location current_location_;
  CourierStatus status_;

  // Constructors

  Courier(CourierId id, CourierName name, Transport transport,
          Location current_location, CourierStatus status)
      : id_(std::move(id)),
        name_(std::move(name)),
        transport_(std::move(transport)),
        current_location_(current_location),
        status_(status) {}

 public:
  [[nodiscard]] static auto Create(CourierName, Transport) -> Courier;

  [[nodiscard]] static auto Hydrate(CourierId, CourierName, Transport, Location,
                                    CourierStatus) -> Courier;

  // Observers

  [[nodiscard]] auto GetId() const noexcept -> CourierId;
  [[nodiscard]] auto GetName() const noexcept -> CourierName;
  [[nodiscard]] auto GetTransport() const noexcept -> Transport;
  [[nodiscard]] auto GetStatus() const noexcept -> CourierStatus;
  [[nodiscard]] auto GetCurrentLocation() const noexcept -> Location;
  [[nodiscard]] auto CalculateTimeToPoint(Location) const noexcept -> Time;

  // Modifiers

  auto MoveTo(Location location) -> void;
  auto StartWork() -> void;
  auto StopWork() -> void;
  auto InWork() -> void;
};

}  // namespace delivery::core::domain::courier
