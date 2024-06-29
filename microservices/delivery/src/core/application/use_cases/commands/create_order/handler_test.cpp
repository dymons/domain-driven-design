#include <userver/utest/utest.hpp>

#include <core/domain/order/order.hpp>
#include <core/ports/order_repository/repository_mock_test.hpp>

#include "handler.hpp"

namespace delivery::core::application::use_cases::commands::create_order {

namespace {

auto const kBasketId = std::string{"basket_id"};
auto const kAddress = std::string{"address"};
auto const kWeight = int{5};

class CreateOrderHandlerShould : public ::testing::Test {
 protected:
  SharedRef<core::ports::IOrderRepository> order_repository_ =
      core::ports::MockOrderRepository();
  SharedRef<ICreateOrderHandler> handler_ =
      MakeCreateOrderHandler(order_repository_);
};

UTEST_F(CreateOrderHandlerShould, CreateOrder) {
  // Arrange
  auto command = CreateOrderCommand{kBasketId, kAddress, kWeight};

  // Act
  ASSERT_NO_THROW(handler_->Handle(std::move(command)));

  // Assert
  ASSERT_NO_THROW(
      order_repository_->GetById(core::domain::order::OrderId{kBasketId}));

  auto const order =
      order_repository_->GetById(core::domain::order::OrderId{kBasketId});
  ASSERT_EQ(order->GetId(), core::domain::order::OrderId{kBasketId});
  ASSERT_EQ(order->GetStatus(), core::domain::order::OrderStatus::kCreated);
  ASSERT_EQ(order->GetCourierId(), std::nullopt);
  ASSERT_EQ(order->GetDeliveryLocation(), core::domain::Location::kMinLocation);
  ASSERT_EQ(order->GetWeight(), core::domain::Weight{kWeight});
  ASSERT_FALSE(order->IsCourierAssigned());
}

}  // namespace

}  // namespace delivery::core::application::use_cases::commands::create_order
