#pragma once

#include <optional>

#include <core/domain/courier/strong_typedefs.hpp>
#include <core/domain/shared_kernel/location.hpp>
#include <core/domain/shared_kernel/weight.hpp>
#include "status.hpp"
#include "strong_typedefs.hpp"

namespace delivery::core::domain::courier {
class Courier;
}  // namespace delivery::core::domain::courier

namespace delivery::core::domain::order {

class Order {
  OrderId id_;
  OrderStatus status_;
  std::optional<courier::CourierId> courier_id_;
  shared_kernel::Location delivery_location_;
  shared_kernel::Weight weight_;

  // Constructors

  Order(OrderId id, OrderStatus status, std::optional<courier::CourierId> courier_id,
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

  auto GetId() const noexcept -> OrderId;
  auto GetStatus() const noexcept -> OrderStatus;
  auto GetCourierId() const noexcept -> std::optional<courier::CourierId>;
  auto GetDeliveryLocation() const noexcept -> shared_kernel::Location;
  auto GetWeight() const noexcept -> shared_kernel::Weight;
  auto IsCourierAssigned() const noexcept -> bool;

  // Modifiers

  auto AssignCourier(courier::Courier& courier) -> void;
  auto Complete() -> void;
};

}  // namespace delivery::core::domain::order
