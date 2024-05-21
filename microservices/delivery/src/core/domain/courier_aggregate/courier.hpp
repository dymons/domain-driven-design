#pragma once

#include <core/domain/shared_kernel/location.hpp>
#include "courier_status.hpp"
#include "strong_typedefs.hpp"
#include "transport.hpp"

namespace delivery::core::domain::courier_aggregate {

class Courier {
  CourierId id_;
  CourierName name_;
  Transport transport_;
  shared_kernel::Location current_location_;
  CourierStatus status_;

  Courier(CourierId id, CourierName name, Transport transport,
          shared_kernel::Location current_location, CourierStatus status)
      : id_(std::move(id)),
        name_(std::move(name)),
        transport_(transport),
        current_location_(current_location),
        status_(status) {}

 public:
  [[nodiscard]] static auto Create(CourierName name,
                                   Transport transport) -> Courier;

  [[nodiscard]] auto GetId() const noexcept -> CourierId;
  [[nodiscard]] auto GetName() const noexcept -> CourierName;
  [[nodiscard]] auto GetTransport() const noexcept -> Transport;
  [[nodiscard]] auto GetCurrentLocation() const noexcept
      -> shared_kernel::Location;
  [[nodiscard]] auto GetStatus() const noexcept -> CourierStatus;
};

}  // namespace delivery::core::domain::courier_aggregate
