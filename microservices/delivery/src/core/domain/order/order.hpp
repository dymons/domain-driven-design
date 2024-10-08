#pragma once

#include <optional>

#include <core/domain/shared_kernel/location/location.hpp>
#include <core/domain/shared_kernel/strong_typedefs.hpp>
#include <core/domain/shared_kernel/weight/weight.hpp>
#include <utils/memory.hpp>
#include "status.hpp"
#include "strong_typedefs.hpp"

namespace delivery::core::domain::order {

// TODO (dymons) Add versioning with optimistic lock

class Order {
  OrderId id_;
  OrderStatus status_;
  std::optional<CourierId> courier_id_;
  Location delivery_location_;
  Weight weight_;

  // Constructors

  Order(OrderId id, OrderStatus status, std::optional<CourierId> courier_id,
        Location delivery_location, Weight weight)
      : id_{std::move(id)},
        status_{status},
        courier_id_{std::move(courier_id)},
        delivery_location_{delivery_location},
        weight_{weight} {}

 public:
  [[nodiscard]] static auto Create(BasketId, Location, Weight)
      -> MutableSharedRef<Order>;

  [[nodiscard]] static auto Hydrate(OrderId, OrderStatus,
                                    std::optional<CourierId>, Location, Weight)
      -> MutableSharedRef<Order>;

  // Observers

  [[nodiscard]] auto GetId() const noexcept -> OrderId;
  [[nodiscard]] auto GetStatus() const noexcept -> OrderStatus;
  [[nodiscard]] auto GetCourierId() const noexcept -> std::optional<CourierId>;
  [[nodiscard]] auto GetDeliveryLocation() const noexcept -> Location;
  [[nodiscard]] auto GetWeight() const noexcept -> Weight;
  [[nodiscard]] auto IsCourierAssigned() const noexcept -> bool;

  [[nodiscard]] auto operator==(const Order&) const -> bool;

  // Modifiers

  auto AssignCourier(CourierId const&) -> void;
  auto Complete() -> void;
};

}  // namespace delivery::core::domain::order

template <>
struct std::hash<delivery::core::domain::order::Order> {
  std::size_t operator()(const delivery::core::domain::order::Order& c) const {
    return std::hash<delivery::core::domain::order::OrderId>{}(c.GetId());
  }
};
