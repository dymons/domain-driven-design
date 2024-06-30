#include <userver/utest/utest.hpp>

#include <core/domain/courier/courier_mock_test.hpp>

#include "exceptions.hpp"
#include "order_mock_test.hpp"

namespace delivery::core::domain::order {

namespace {

UTEST(OrderShould, AssignCourier) {
  // Arrange
  auto order = MockOrder();
  auto courier = courier::MockCourier();
  courier->StartWork();

  // Act
  order->AssignCourier(CourierId{courier->GetId().GetUnderlying()});

  // Assert
  ASSERT_TRUE(order->IsCourierAssigned());
}

UTEST(OrderShould, CompleteOrderWhenOrderIsAssigned) {
  // Arrange
  auto order = MockOrder();
  auto courier = courier::MockCourier();
  courier->StartWork();
  order->AssignCourier(CourierId{courier->GetId().GetUnderlying()});

  // Act
  order->Complete();

  // Assert
  ASSERT_TRUE(order->GetStatus().IsCompleted());
}

UTEST(OrderShould, ThrowWhenCompleteOrderWithStatusCreated) {
  // Arrange
  auto order = MockOrder();

  // Act & Assert
  ASSERT_TRUE(order->GetStatus().IsCreated());
  ASSERT_THROW(order->Complete(), CantCompletedNotAssignedOrder);
}

UTEST(OrderShould, DoNothingWhenCompleteOrderWithStatusCompleted) {
  // Arrange
  auto order = MockOrder();
  auto courier = courier::MockCourier();
  courier->StartWork();
  order->AssignCourier(CourierId{courier->GetId().GetUnderlying()});
  order->Complete();

  // Act
  order->Complete();

  // Assert
  ASSERT_TRUE(order->GetStatus().IsCompleted());
}

}  // namespace

}  // namespace delivery::core::domain::order
