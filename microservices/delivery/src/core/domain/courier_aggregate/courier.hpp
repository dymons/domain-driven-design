#pragma once

#include <core/domain/shared_kernel/location.hpp>
#include "courier_status.hpp"
#include "strong_typedefs.hpp"
#include "transport.hpp"

namespace delivery::core::domain::courier_aggregate {

class Courier {
  CourierId courier_id_;
  CourierName courier_name_;
  Transport transport_;
  shared_kernel::Location current_location_;
  CourierStatus status_;

  Courier(CourierId courier_id, CourierName courier_name, Transport transport,
          shared_kernel::Location current_location, CourierStatus status)
      : courier_id_(std::move(courier_id)),
        courier_name_(std::move(courier_name)),
        transport_(transport),
        current_location_(current_location),
        status_(status) {}

 public:
  [[nodiscard]] static Courier Create(CourierName courier_name,
                                      Transport transport);
};

}  // namespace delivery::core::domain::courier_aggregate
