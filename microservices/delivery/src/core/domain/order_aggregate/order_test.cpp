#include <userver/utest/utest.hpp>

#include <userver/utils/uuid7.hpp>

#include "exceptions.hpp"
#include "order.hpp"

namespace delivery::core::domain::order_aggregate {

namespace {

auto MockBasketId() -> BasketId {
  static const auto kBasketId = userver::utils::generators::GenerateUuidV7();
  return BasketId{kBasketId};
}

auto MockLocation() -> shared_kernel::Location {
  return shared_kernel::Location::Create(shared_kernel::X{5},
                                         shared_kernel::Y{5});
}

auto MockWeight() -> shared_kernel::Weight {
  return shared_kernel::Weight::Create(10);
}

auto MockCourierId() -> CourierId {
  static const auto kCourierId = userver::utils::generators::GenerateUuidV7();
  return CourierId{kCourierId};
}

}  // namespace

UTEST(OrderShould, BeConstructibleWithRequiredProperties) {
  // Arrange

  // Act
  auto order = Order::Create(MockBasketId(), MockLocation(), MockWeight());

  // Assert
  EXPECT_EQ(order.GetOrderId(), OrderId{MockBasketId().GetUnderlying()});
  EXPECT_EQ(order.GetOrderStatus(), OrderStatus::Created);
  EXPECT_EQ(order.GetCourierId(), std::nullopt);
  EXPECT_EQ(order.GetLocation(), MockLocation());
  EXPECT_EQ(order.GetWeight(), MockWeight());
}

UTEST(OrderShould, AssignCourier) {
  // Arrange
  auto order = Order::Create(MockBasketId(), MockLocation(), MockWeight());

  // Act
  order.AssignCourier(MockCourierId());

  // Assert
  EXPECT_TRUE(order.IsCourierAssigned());
  EXPECT_EQ(order.GetOrderStatus(), OrderStatus::Assigned);
  EXPECT_EQ(order.GetCourierId(), MockCourierId());
}

UTEST(OrderShould, CompleteOrderWhenOrderIsAssigned) {
  // Arrange
  auto order = Order::Create(MockBasketId(), MockLocation(), MockWeight());
  order.AssignCourier(MockCourierId());

  // Act
  order.Complete();

  // Assert
  EXPECT_EQ(order.GetOrderStatus(), OrderStatus::Completed);
  EXPECT_EQ(order.GetCourierId(), MockCourierId());
}

UTEST(OrderShould, ThrowWhenCompleteOrderWithStatusCreated) {
  // Arrange
  auto order = Order::Create(MockBasketId(), MockLocation(), MockWeight());

  // Act & Assert
  EXPECT_EQ(order.GetOrderStatus(), OrderStatus::Created);
  EXPECT_THROW(order.Complete(), IllegalStateException);
}

UTEST(OrderShould, ThrowWhenCompleteOrderWithStatusCompleted) {
  // Arrange
  auto order = Order::Create(MockBasketId(), MockLocation(), MockWeight());
  order.AssignCourier(MockCourierId());
  order.Complete();

  // Act & Assert
  EXPECT_EQ(order.GetOrderStatus(), OrderStatus::Completed);
  EXPECT_THROW(order.Complete(), IllegalStateException);
}

}  // namespace delivery::core::domain::order_aggregate
