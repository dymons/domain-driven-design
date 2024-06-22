#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "query.hpp"
#include "response.hpp"

namespace delivery::core::application::use_cases::queries::get_couriers {

class IGetCouriersHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IGetCouriersHandler() = default;

  virtual auto Handle(GetCouriersQuery&&) const -> Response = 0;
};

}  // namespace delivery::core::application::use_cases::queries::get_couriers
