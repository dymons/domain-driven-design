#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "query.hpp"
#include "response.hpp"

namespace delivery::core::application::use_cases::queries::get_orders {

class IGetOrdersHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IGetOrdersHandler() = default;

  virtual auto Handle(GetOrdersQuery&&) const -> Response = 0;
};

}  // namespace delivery::core::application::use_cases::queries::get_orders
