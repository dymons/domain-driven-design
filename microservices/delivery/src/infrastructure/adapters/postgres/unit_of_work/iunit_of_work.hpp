#pragma once

#include <functional>

#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

class IUnitOfWork : private NonCopyableAndMoveable {
 public:
  virtual ~IUnitOfWork() = default;

  virtual auto RunTransaction(
      std::function<void(SharedRef<IRunTransactionContext>)>) const -> void = 0;
};

}  // namespace delivery::infrastructure::adapters::postgres
