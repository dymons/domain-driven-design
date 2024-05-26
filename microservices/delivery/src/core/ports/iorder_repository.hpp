#pragma once

#include <vector>

#include <core/domain/order/strong_typedefs.hpp>

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::core::ports {

class IOrderRepository {
 public:
  virtual ~IOrderRepository() = default;

  IOrderRepository() = default;
  IOrderRepository(IOrderRepository const&) = delete;
  IOrderRepository(IOrderRepository&&) = delete;
  IOrderRepository& operator=(IOrderRepository const&) = delete;
  IOrderRepository& operator=(IOrderRepository&&) = delete;

  virtual auto Add(domain::order::Order const&) const -> void = 0;
  virtual auto Update(domain::order::Order const&) const -> void = 0;
  virtual auto GetById(domain::order::OrderId const&) const
      -> domain::order::Order = 0;
  virtual auto GetAllNotAssigned() const
      -> std::vector<domain::order::Order> = 0;
  virtual auto GetAllAssigned() const -> std::vector<domain::order::Order> = 0;
};

}  // namespace delivery::core::ports
