#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

namespace delivery::core::application::use_cases::commands::stop_work {

class IStopWorkHandler : private NonCopyableAndMoveable {
 public:
  virtual ~IStopWorkHandler() = default;

  virtual auto Handle(StopWorkCommand&&) const -> void = 0;
};

}  // namespace delivery::core::application::use_cases::commands::stop_work
