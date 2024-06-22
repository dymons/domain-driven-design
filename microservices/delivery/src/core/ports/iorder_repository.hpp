#pragma once

#include <vector>

#include <core/domain/order/strong_typedefs.hpp>
#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::core::ports {

struct OrderNotFound final : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct OrderAlreadyExists final : std::runtime_error {
  using std::runtime_error::runtime_error;
};

class IOrderRepository : private NonCopyableAndMoveable {
 public:
  virtual ~IOrderRepository() = default;

  virtual auto Add(SharedRef<core::domain::order::Order> const&) const
      -> void = 0;
  virtual auto Update(SharedRef<core::domain::order::Order> const&) const
      -> void = 0;
  virtual auto GetById(core::domain::order::OrderId const&) const
      -> MutableSharedRef<core::domain::order::Order> = 0;
  virtual auto GetNotAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> = 0;
  virtual auto GetAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> = 0;
  virtual auto GetOrders() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> = 0;
};

}  // namespace delivery::core::ports
