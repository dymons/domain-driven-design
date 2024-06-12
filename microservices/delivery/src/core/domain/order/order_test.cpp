#include <userver/utest/utest.hpp>

#include <userver/utils/uuid7.hpp>

#include <core/domain/courier/courier.hpp>
#include "order_mock_test.hpp"

namespace delivery::core::domain::order {

namespace {

auto MockCourier(
    courier::CourierStatus status = courier::CourierStatus::kNotAvailable)
    -> courier::Courier {
  return courier::Courier::Hydrate(
      courier::CourierId{"CourierId"}, courier::CourierName{"CourierName"},
      courier::Transport::kPedestrian, Location::kMinLocation, status);
}

UTEST(OrderShould, AssignCourier) {
  // Arrange
  auto order = MockOrder();
  auto courier = MockCourier(courier::CourierStatus::kReady);

  // Act
  order.AssignCourier(CourierId{courier.GetId().GetUnderlying()});

  // Assert
  ASSERT_TRUE(order.IsCourierAssigned());
}

UTEST(OrderShould, CompleteOrderWhenOrderIsAssigned) {
  // Arrange
  auto order = MockOrder();
  auto courier = MockCourier();
  courier.StartWork();
  order.AssignCourier(CourierId{courier.GetId().GetUnderlying()});

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
  order.AssignCourier(CourierId{courier.GetId().GetUnderlying()});
  order.Complete();

  // Act
  order.Complete();

  // Assert
  ASSERT_TRUE(order.GetStatus().IsCompleted());
}

}  // namespace

}  // namespace delivery::core::domain::order
