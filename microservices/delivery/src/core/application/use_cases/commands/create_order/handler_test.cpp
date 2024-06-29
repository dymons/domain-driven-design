#include <userver/utest/utest.hpp>

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
  EXPECT_NO_THROW(handler_->Handle(std::move(command)));

  // Assert
  EXPECT_NO_THROW(
      order_repository_->GetById(core::domain::order::OrderId{kBasketId}));
}

}  // namespace

}  // namespace delivery::core::application::use_cases::commands::create_order
