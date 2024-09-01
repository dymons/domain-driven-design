#pragma once

#include <optional>
#include <vector>

#include <core/domain/courier/fwd.hpp>
#include <core/domain/order/fwd.hpp>
#include <utils/memory.hpp>
#include <utils/non_copyable_and_moveable.hpp>

namespace delivery::core::domain_services {

// TODO (dymons) Maybe inject ICourierRepository?

class IDispatchService : private NonCopyableAndMoveable {
 public:
  virtual ~IDispatchService() = default;

  struct DispatchResult final {
    MutableSharedRef<domain::order::Order> order;
    std::optional<MutableSharedRef<domain::courier::Courier>> courier;
  };

  [[nodiscard]] virtual auto Dispatch(
      MutableSharedRef<domain::order::Order>&&,
      std::vector<MutableSharedRef<domain::courier::Courier>>&&) const
      -> DispatchResult = 0;
};

}  // namespace delivery::core::domain_services
