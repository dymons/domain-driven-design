#pragma once

#include <unordered_set>

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

  [[nodiscard]] virtual auto Dispatch(
      domain::order::Order&& order,
      std::unordered_set<domain::courier::Courier> const& couriers) const
      -> domain::order::Order = 0;
};

}  // namespace delivery::core::domain_services
