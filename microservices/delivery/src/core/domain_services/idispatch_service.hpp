#pragma once

#include <optional>
#include <unordered_set>

#include <utils/memory.hpp>

namespace delivery::core::domain::courier {
class Courier;
}  // namespace delivery::core::domain::courier

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::core::domain_services {

class IDispatchService {
 public:
  virtual ~IDispatchService() = default;

  IDispatchService() = default;
  IDispatchService(IDispatchService const&) = delete;
  IDispatchService(IDispatchService&&) = delete;
  IDispatchService& operator=(IDispatchService const&) = delete;
  IDispatchService& operator=(IDispatchService&&) = delete;

  struct DispatchResult {
    SharedRef<domain::order::Order> order;
    std::optional<SharedRef<domain::courier::Courier>> courier;
  };

  [[nodiscard]] virtual auto Dispatch(
      domain::order::Order&& order,
      std::unordered_set<domain::courier::Courier>&& couriers) const
      -> DispatchResult = 0;
};

}  // namespace delivery::core::domain_services
