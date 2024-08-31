#pragma once

#include <core/domain/shared_kernel/location/location.hpp>
#include <core/domain/shared_kernel/strong_typedefs.hpp>
#include <utils/memory.hpp>

#include "exceptions.hpp"
#include "status.hpp"
#include "strong_typedefs.hpp"
#include "transport.hpp"

namespace delivery::core::domain::courier {

// TODO (dymons) Add versioning with optimistic lock

class Courier {
  CourierId id_;
  CourierName name_;
  Transport transport_;
  Location current_location_;
  CourierStatus status_;

  // Constructors

  Courier(CourierId id, CourierName name, Transport transport,
          Location current_location, CourierStatus status)
      : id_{std::move(id)},
        name_{std::move(name)},
        transport_{std::move(transport)},
        current_location_{current_location},
        status_{status} {}

 public:
  [[nodiscard]] static auto Create(CourierName, Transport)
      -> MutableSharedRef<Courier>;

  [[nodiscard]] static auto Hydrate(CourierId, CourierName, Transport, Location,
                                    CourierStatus) -> MutableSharedRef<Courier>;

  // Observers

  [[nodiscard]] auto GetId() const noexcept -> CourierId;
  [[nodiscard]] auto GetName() const noexcept -> CourierName;
  [[nodiscard]] auto GetTransport() const noexcept -> Transport;
  [[nodiscard]] auto GetStatus() const noexcept -> CourierStatus;
  [[nodiscard]] auto GetCurrentLocation() const noexcept -> Location;
  [[nodiscard]] auto CalculateTimeToPoint(Location) const noexcept -> Time;

  [[nodiscard]] auto operator==(const Courier&) const -> bool;

  // Modifiers

  auto MoveTo(Location location) -> void;
  auto StartWork() -> void;
  auto StopWork() -> void;
  auto InWork() -> void;
  auto CompleteOrder() -> void;
};

}  // namespace delivery::core::domain::courier

template <>
struct std::hash<delivery::core::domain::courier::Courier> {
  std::size_t operator()(
      const delivery::core::domain::courier::Courier& c) const {
    return std::hash<delivery::core::domain::CourierId>{}(c.GetId());
  }
};
