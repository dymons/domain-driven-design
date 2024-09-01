#pragma once

#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

class IUnitOfWork : private NonCopyableAndMoveable {
 public:
  virtual ~IUnitOfWork() = default;
};

}  // namespace delivery::infrastructure::adapters::postgres
