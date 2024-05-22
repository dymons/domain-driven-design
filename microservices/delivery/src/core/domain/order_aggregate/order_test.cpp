#include <userver/utest/utest.hpp>

#include <userver/utils/uuid7.hpp>

#include <core/domain/courier_aggregate/courier.hpp>
#include "exceptions.hpp"
#include "order.hpp"

namespace delivery::core::domain::order_aggregate {

namespace {

auto MockBasketId() -> BasketId {
  static const auto kBasketId = userver::utils::generators::GenerateUuidV7();
  return BasketId{kBasketId};
}

auto MockDeliveryLocation() -> shared_kernel::Location {
  return shared_kernel::Location::Create(shared_kernel::X{5},
                                         shared_kernel::Y{5});
}

auto MockWeight() -> shared_kernel::Weight {
  return shared_kernel::Weight::Create(10);
}

auto MockCourier() -> courier_aggregate::Courier {
  return courier_aggregate::Courier::Create(
      courier_aggregate::CourierName{"CourierName"},
      courier_aggregate::Transport{});
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
  EXPECT_EQ(order.GetId(), OrderId{MockBasketId().GetUnderlying()});
  EXPECT_EQ(order.GetStatus(), OrderStatus::Created);
  EXPECT_EQ(order.GetCourierId(), std::nullopt);
  EXPECT_EQ(order.GetDeliveryLocation(), MockDeliveryLocation());
  EXPECT_EQ(order.GetWeight(), MockWeight());
}

UTEST(OrderShould, AssignCourier) {
  // Arrange
  auto order = MockOrder();

  // Act
  order.AssignCourier(MockCourier());

  // Assert
  EXPECT_TRUE(order.IsCourierAssigned());
}

UTEST(OrderShould, CompleteOrderWhenOrderIsAssigned) {
  // Arrange
  auto order = MockOrder();
  order.AssignCourier(MockCourier());

  // Act
  order.Complete();

  // Assert
  EXPECT_EQ(order.GetStatus(), OrderStatus::Completed);
}

UTEST(OrderShould, ThrowWhenCompleteOrderWithStatusCreated) {
  // Arrange
  auto order = MockOrder();

  // Act & Assert
  EXPECT_EQ(order.GetStatus(), OrderStatus::Created);
  EXPECT_THROW(order.Complete(), CanNotCompleteOrderWithoutCourier);
}

UTEST(OrderShould, DoNothingWhenCompleteOrderWithStatusCompleted) {
  // Arrange
  auto order = MockOrder();
  order.AssignCourier(MockCourier());
  order.Complete();

  // Act
  order.Complete();

  // Assert
  EXPECT_EQ(order.GetStatus(), OrderStatus::Completed);
}

}  // namespace delivery::core::domain::order_aggregate
