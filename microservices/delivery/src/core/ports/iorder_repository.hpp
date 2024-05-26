#pragma once

#include <vector>

#include <core/domain/order/strong_typedefs.hpp>

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::core::ports {

class IOrderRepository {
  using Order = domain::order::Order;
  using OrderId = domain::order::OrderId;

 public:
  virtual ~IOrderRepository() = default;

  IOrderRepository() = default;
  IOrderRepository(IOrderRepository const&) = delete;
  IOrderRepository(IOrderRepository&&) = delete;
  IOrderRepository& operator=(IOrderRepository const&) = delete;
  IOrderRepository& operator=(IOrderRepository&&) = delete;

  virtual auto Add(Order const&) const -> void = 0;
  virtual auto Update(Order const&) const -> void = 0;
  virtual auto GetById(OrderId const&) const -> Order = 0;
  virtual auto GetAllNotAssigned() const -> std::vector<Order> = 0;
  virtual auto GetAllAssigned() const -> std::vector<Order> = 0;
};

}  // namespace delivery::core::ports
