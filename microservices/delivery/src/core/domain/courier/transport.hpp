#pragma once

#include <core/domain/shared_kernel/weight/weight.hpp>
#include "strong_typedefs.hpp"

namespace delivery::core::domain::courier {

class Transport {
  TransportId id_;
  TransportName name_;
  Speed speed_;
  Weight capacity_;

  // Constructors

  Transport(TransportId id, TransportName name, Speed speed, Weight capacity)
      : id_{id}, name_{std::move(name)}, speed_{speed}, capacity_{capacity} {}

 public:
  static auto Hydrate(TransportId, TransportName, Speed, Weight) -> Transport;

  static const Transport kPedestrian;
  static const Transport kBicycle;
  static const Transport kScooter;
  static const Transport kCar;

  // Observers

  [[nodiscard]] auto GetId() const -> TransportId;
  [[nodiscard]] auto GetName() const -> TransportName;
  [[nodiscard]] auto GetSpeed() const -> Speed;
  [[nodiscard]] auto GetCapacity() const -> Weight;
};

}  // namespace delivery::core::domain::courier
