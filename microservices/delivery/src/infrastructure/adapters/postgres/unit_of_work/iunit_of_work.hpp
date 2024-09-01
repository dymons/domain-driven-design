#pragma once

#include <functional>

#include <core/ports/courier_repository/fwd.hpp>
#include <core/ports/order_repository/fwd.hpp>
#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

#include "fwd.hpp"

namespace delivery::infrastructure::adapters::postgres {

class IUnitOfWork : private NonCopyableAndMoveable {
 public:
  virtual ~IUnitOfWork() = default;

  virtual auto RunTransaction(std::function<void()>) -> void = 0;

  [[nodiscard]] virtual auto GetCourierRepository()
      -> SharedRef<core::ports::ICourierRepository> = 0;

  [[nodiscard]] virtual auto GetOrderRepository()
      -> SharedRef<core::ports::IOrderRepository> = 0;
};

}  // namespace delivery::infrastructure::adapters::postgres
