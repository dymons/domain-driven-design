#pragma once

#include <vector>

#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

class IGetActiveOrdersHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IGetActiveOrdersHandler() = default;

  [[nodiscard]] virtual auto Handle(GetActiveOrdersQuery&&) const
      -> std::vector<Order> = 0;
};

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
