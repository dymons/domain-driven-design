#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "command.hpp"

namespace delivery::core::application::use_cases::commands::start_work {

class IStartWorkHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IStartWorkHandler() = default;

  virtual auto Handle(StartWorkCommand&&) const -> void = 0;
};

}  // namespace delivery::core::application::use_cases::commands::start_work
