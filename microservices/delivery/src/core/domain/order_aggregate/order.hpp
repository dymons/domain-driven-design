#pragma once

#include <optional>

#include <core/domain/shared_kernel/location.hpp>
#include <core/domain/shared_kernel/weight.hpp>
#include "order_status.hpp"
#include "strong_typedefs.hpp"

namespace delivery::core::domain::order_aggregate {

class Order {
  OrderId order_id_;
  OrderStatus status_;
  std::optional<CourierId> courier_id_;
  shared_kernel::Location location_;
  shared_kernel::Weight weight_;

  Order(OrderId order_id, OrderStatus status,
        std::optional<CourierId> courier_id, shared_kernel::Location location,
        shared_kernel::Weight weight)
      : order_id_(std::move(order_id)),
        status_(status),
        courier_id_(std::move(courier_id)),
        location_(location),
        weight_(weight) {}

 public:
  [[nodiscard]] static auto Create(BasketId basket_id,
                                   shared_kernel::Location location,
                                   shared_kernel::Weight weight) -> Order;

  [[nodiscard]] auto GetOrderId() const noexcept -> OrderId;
  [[nodiscard]] auto GetOrderStatus() const noexcept -> OrderStatus;
  [[nodiscard]] auto GetCourierId() const noexcept -> std::optional<CourierId>;
  [[nodiscard]] auto GetLocation() const noexcept -> shared_kernel::Location;
  [[nodiscard]] auto GetWeight() const noexcept -> shared_kernel::Weight;

  auto AssignCourier(CourierId courier_id) -> void;

  auto Complete() -> void;
};

}  // namespace delivery::core::domain::order_aggregate
