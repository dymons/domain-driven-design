#pragma once

#include <vector>

#include <core/domain/order/strong_typedefs.hpp>

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::core::ports {

struct OrderNotFound : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct OrderAlreadyExists : std::runtime_error {
  using std::runtime_error::runtime_error;
};

class IOrderRepository {
 public:
  virtual ~IOrderRepository() = default;

  IOrderRepository() = default;
  IOrderRepository(IOrderRepository const&) = delete;
  IOrderRepository(IOrderRepository&&) = delete;
  IOrderRepository& operator=(IOrderRepository const&) = delete;
  IOrderRepository& operator=(IOrderRepository&&) = delete;

  virtual auto Add(core::domain::order::Order const&) const -> void = 0;
  virtual auto Update(core::domain::order::Order const&) const -> void = 0;
  virtual auto GetById(core::domain::order::OrderId const&) const
      -> core::domain::order::Order = 0;
  virtual auto GetNotAssigned() const
      -> std::vector<core::domain::order::Order> = 0;
  virtual auto GetAssigned() const
      -> std::vector<core::domain::order::Order> = 0;
};

}  // namespace delivery::core::ports
