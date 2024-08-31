#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

// clang-format off
namespace delivery::core::application::use_cases::commands::move_courier_to_order {
// clang-format on

class IMoveCourierToOrderHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IMoveCourierToOrderHandler() = default;

  virtual auto Handle(MoveCourierToOrderCommand&&) const -> void = 0;
};

// clang-format off
}  // namespace delivery::core::application::use_cases::commands::move_courier_to_order
// clang-format on
