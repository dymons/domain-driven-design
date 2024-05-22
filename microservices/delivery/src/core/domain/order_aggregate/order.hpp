#pragma once

#include <optional>

#include <core/domain/courier_aggregate/strong_typedefs.hpp>
#include <core/domain/shared_kernel/location.hpp>
#include <core/domain/shared_kernel/weight.hpp>
#include "order_status.hpp"
#include "strong_typedefs.hpp"

namespace delivery::core::domain::courier_aggregate {
class Courier;
}  // namespace delivery::core::domain::courier_aggregate

namespace delivery::core::domain::order_aggregate {

class Order {
  OrderId id_;
  OrderStatus status_;
  std::optional<courier_aggregate::CourierId> courier_id_;
  shared_kernel::Location delivery_location_;
  shared_kernel::Weight weight_;

  // Constructors

  Order(OrderId id, OrderStatus status,
        std::optional<courier_aggregate::CourierId> courier_id,
        shared_kernel::Location delivery_location, shared_kernel::Weight weight)
      : id_(std::move(id)),
        status_(status),
        courier_id_(std::move(courier_id)),
        delivery_location_(delivery_location),
        weight_(weight) {}

 public:
  [[nodiscard]] static auto Create(BasketId basket_id,
                                   shared_kernel::Location delivery_location,
                                   shared_kernel::Weight weight) -> Order;

  // Observers

  auto GetId() const -> OrderId;
  auto GetStatus() const -> OrderStatus;
  auto GetCourierId() const -> std::optional<courier_aggregate::CourierId>;
  auto GetDeliveryLocation() const -> shared_kernel::Location;
  auto GetWeight() const -> shared_kernel::Weight;
  auto IsCourierAssigned() const -> bool;

  // Modifiers

  auto Assign(courier_aggregate::Courier const& courier) -> void;
  auto Complete() -> void;
};

}  // namespace delivery::core::domain::order_aggregate
