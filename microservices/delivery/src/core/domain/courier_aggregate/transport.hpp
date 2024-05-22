#pragma once

#include <core/domain/shared_kernel/weight.hpp>
#include "strong_typedefs.hpp"

namespace delivery::core::domain::courier_aggregate {

class Transport {
  TransportId id_;
  TransportName name_;
  Speed speed_;
  shared_kernel::Weight capacity_;

  // Constructors

  Transport(TransportId id, TransportName name, Speed speed,
            shared_kernel::Weight capacity)
      : id_(id), name_(std::move(name)), speed_(speed), capacity_(capacity) {}

 public:
  static const Transport kPedestrian;
  static const Transport kBicycle;
  static const Transport kScooter;
  static const Transport kCar;

  // Observers

  auto GetId() const -> TransportId;
  auto GetName() const -> TransportName;
  auto GetSpeed() const -> Speed;
  auto GetCapacity() const -> shared_kernel::Weight;
};

}  // namespace delivery::core::domain::courier_aggregate
