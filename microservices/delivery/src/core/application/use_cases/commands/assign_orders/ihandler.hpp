#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "command.hpp"

namespace delivery::core::application::use_cases::commands::assign_orders {

class IAssignOrdersHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IAssignOrdersHandler() = default;

  virtual auto Handle(AssignOrdersCommand&&) const -> void = 0;
};

}  // namespace delivery::core::application::use_cases::commands::assign_orders
