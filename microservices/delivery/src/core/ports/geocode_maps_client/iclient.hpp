#pragma once

#include <string>

#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

#include "ilocation.hpp"

namespace delivery::core::ports {

class IGeocodeMapsClient : private NonCopyableAndMoveable {
 public:
  virtual ~IGeocodeMapsClient() = default;

  [[nodiscard]] virtual auto Geocode(std::string const&) const
      -> SharedRef<IGeocodeMapsLocation> = 0;
};

}  // namespace delivery::core::ports
