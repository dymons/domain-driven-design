#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "query.hpp"
#include "response.hpp"

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

class IGetOrdersHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IGetOrdersHandler() = default;

  virtual auto Handle(GetOrdersQuery&&) const -> Response = 0;
};

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
