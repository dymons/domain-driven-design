#include <userver/utest/utest.hpp>

#include <userver/utils/uuid7.hpp>

#include <core/domain/courier/courier.hpp>
#include "exceptions.hpp"
#include "order.hpp"

namespace delivery::core::domain::order {

namespace {

auto MockBasketId() -> BasketId {
  static const auto kBasketId = userver::utils::generators::GenerateUuidV7();
  return BasketId{kBasketId};
}

auto MockDeliveryLocation() -> Location { return Location::Create(X{5}, Y{5}); }

auto MockWeight() -> Weight { return Weight{10}; }

auto MockCourier(
    courier::CourierStatus status = courier::CourierStatus::kNotAvailable)
    -> courier::Courier {
  return courier::Courier::Hydrate(
      courier::CourierId{"CourierId"}, courier::CourierName{"CourierName"},
      courier::Transport::kPedestrian, Location::kMinLocation, status);
}

auto MockOrder() -> Order {
  return Order::Create(MockBasketId(), MockDeliveryLocation(), MockWeight());
}

}  // namespace

UTEST(OrderShould, BeConstructibleWithRequiredProperties) {
  // Arrange

  // Act
  auto const order = MockOrder();

  // Assert
  ASSERT_EQ(order.GetId(), OrderId{MockBasketId().GetUnderlying()});
  ASSERT_TRUE(order.GetStatus().IsCreated());
  ASSERT_EQ(order.GetCourierId(), std::nullopt);
  ASSERT_EQ(order.GetDeliveryLocation(), MockDeliveryLocation());
  ASSERT_EQ(order.GetWeight(), MockWeight());
}

UTEST(OrderShould, AssignCourier) {
  // Arrange
  auto order = MockOrder();
  auto courier = MockCourier(courier::CourierStatus::kReady);

  // Act
  order.AssignCourier(courier);

  // Assert
  ASSERT_TRUE(order.IsCourierAssigned());
  ASSERT_TRUE(courier.GetStatus().IsBusy());
}

UTEST(OrderShould, ThrowWhenAssignBusyCourier) {
  // Arrange
  auto order = MockOrder();
  auto courier = MockCourier(courier::CourierStatus::kBusy);

  // Act

  // Assert
  ASSERT_THROW(order.AssignCourier(courier), CantAssignOrderToBusyCourier);
}

UTEST(OrderShould, CompleteOrderWhenOrderIsAssigned) {
  // Arrange
  auto order = MockOrder();
  auto courier = MockCourier();
  courier.StartWork();
  order.AssignCourier(courier);

  // Act
  order.Complete();

  // Assert
  ASSERT_TRUE(order.GetStatus().IsCompleted());
}

UTEST(OrderShould, ThrowWhenCompleteOrderWithStatusCreated) {
  // Arrange
  auto order = MockOrder();

  // Act & Assert
  ASSERT_TRUE(order.GetStatus().IsCreated());
  ASSERT_THROW(order.Complete(), CantCompletedNotAssignedOrder);
}

UTEST(OrderShould, DoNothingWhenCompleteOrderWithStatusCompleted) {
  // Arrange
  auto order = MockOrder();
  auto courier = MockCourier(courier::CourierStatus::kReady);
  order.AssignCourier(courier);
  order.Complete();

  // Act
  order.Complete();

  // Assert
  ASSERT_TRUE(order.GetStatus().IsCompleted());
}

}  // namespace delivery::core::domain::order
