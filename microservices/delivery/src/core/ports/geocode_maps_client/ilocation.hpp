#pragma once

#include <core/domain/shared_kernel/location/location.hpp>
#include <utils/non_copyable_and_moveable.hpp>

namespace delivery::core::ports {

class ILocation : private NonCopyableAndMoveable {
 public:
  virtual ~ILocation() = default;

  virtual auto GetLocation() const -> core::domain::Location = 0;
};

}  // namespace delivery::core::ports
