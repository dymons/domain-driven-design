#pragma once

#include <vector>

#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

namespace delivery::core::application::use_cases::queries::get_couriers {

class IGetCouriersHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IGetCouriersHandler() = default;

  [[nodiscard]] virtual auto Handle(GetCouriersQuery&&) const
      -> std::vector<Courier> = 0;
};

}  // namespace delivery::core::application::use_cases::queries::get_couriers
