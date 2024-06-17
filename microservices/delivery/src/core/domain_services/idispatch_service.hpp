#pragma once

#include <optional>
#include <unordered_set>

#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

namespace delivery::core::domain::courier {
class Courier;
}  // namespace delivery::core::domain::courier

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::core::domain_services {

class IDispatchService : private NonCopyableAndMoveable {
 public:
  virtual ~IDispatchService() = default;

  struct DispatchResult final {
    MutableSharedRef<domain::order::Order> order;
    std::optional<MutableSharedRef<domain::courier::Courier>> courier;
  };

  [[nodiscard]] virtual auto Dispatch(
      MutableSharedRef<domain::order::Order>&&,
      std::unordered_set<MutableSharedRef<domain::courier::Courier>>&&) const
      -> DispatchResult = 0;
};

}  // namespace delivery::core::domain_services
