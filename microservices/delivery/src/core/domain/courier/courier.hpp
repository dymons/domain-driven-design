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
  Status status_;

  // Constructors

  Courier(CourierId id, CourierName name, Transport transport,
          shared_kernel::Location current_location, Status status)
      : id_(std::move(id)),
        name_(std::move(name)),
        transport_(std::move(transport)),
        current_location_(current_location),
        status_(status) {}

 public:
  /*!
    \brief
        Factory method, constructs Courier with name and transport
  */
  [[nodiscard]] static auto Create(CourierName name,
                                   Transport transport) -> Courier;

  /*!
    \brief
        Hydrate method, restore object without validation
  */
  [[nodiscard]] static auto Hydrate(CourierId id, CourierName name,
                                    Transport transport,
                                    shared_kernel::Location current_location,
                                    Status status) -> Courier;

  // Observers

  auto GetId() const noexcept -> CourierId;
  auto GetName() const noexcept -> CourierName;
  auto GetTransport() const noexcept -> Transport;
  auto GetCurrentLocation() const noexcept -> shared_kernel::Location;
  auto GetStatus() const noexcept -> Status;
  auto CalculateTimeToPoint(shared_kernel::Location) const noexcept -> Time;

  // Modifiers

  auto MoveTo(shared_kernel::Location location) -> void;
  auto StartWork() -> void;
  auto StopWork() -> void;
  auto InWork() -> void;
};

}  // namespace delivery::core::domain::courier