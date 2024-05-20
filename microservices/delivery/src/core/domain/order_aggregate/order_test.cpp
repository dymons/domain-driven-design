#include <userver/utest/utest.hpp>

#include <userver/utils/uuid7.hpp>

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

}  // namespace delivery::core::domain::order_aggregate
