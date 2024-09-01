#pragma once

#include <core/ports/courier_repository/fwd.hpp>
#include <core/ports/order_repository/fwd.hpp>
#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

class IRunTransactionContext : private NonCopyableAndMoveable {
 public:
  virtual ~IRunTransactionContext() = default;

  [[nodiscard]] virtual auto GetCourierRepository() const
      -> SharedRef<core::ports::ICourierRepository> = 0;

  [[nodiscard]] virtual auto GetOrderRepository() const
      -> SharedRef<core::ports::IOrderRepository> = 0;
};

}  // namespace delivery::infrastructure::adapters::postgres
