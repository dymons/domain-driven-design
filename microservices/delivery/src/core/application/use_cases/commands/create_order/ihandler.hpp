#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "command.hpp"

namespace delivery::core::application::use_cases::commands::create_order {

class ICreateOrderHandler : private NonCopyableAndMoveable {
 public:
  virtual ~ICreateOrderHandler() = default;

  virtual auto Handle(CreateOrderCommand&&) const -> void = 0;
};

}  // namespace delivery::core::application::use_cases::commands::create_order
