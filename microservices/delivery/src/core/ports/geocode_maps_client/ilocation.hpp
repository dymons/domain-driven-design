#pragma once

#include <core/domain/shared_kernel/location/location.hpp>
#include <utils/non_copyable_and_moveable.hpp>

namespace delivery::core::ports {

class IGeocodeMapsLocation : private NonCopyableAndMoveable {
 public:
  virtual ~IGeocodeMapsLocation() = default;

  [[nodiscard]] virtual auto GetLocation() const -> core::domain::Location = 0;
};

}  // namespace delivery::core::ports
