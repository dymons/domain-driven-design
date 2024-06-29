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
 private:
  SharedRef<core::ports::IOrderRepository> mock_order_repository_ =
      core::ports::MockOrderRepository();

 protected:
  SharedRef<ICreateOrderHandler> handler_ =
      MakeCreateOrderHandler(mock_order_repository_);
};

UTEST_F(CreateOrderHandlerShould, CreateOrder) {
  // Arrange
  auto command = CreateOrderCommand{kBasketId, kAddress, kWeight};

  // Act & Assert
  ASSERT_NO_THROW(handler_->Handle(std::move(command)));
}

UTEST_F(CreateOrderHandlerShould, IdempotencyCreateOrder) {
  // Arrange
  auto const command = CreateOrderCommand{kBasketId, kAddress, kWeight};

  // Act & Assert
  ASSERT_NO_THROW(handler_->Handle(CreateOrderCommand{command}));
  ASSERT_NO_THROW(handler_->Handle(CreateOrderCommand{command}));
}

}  // namespace

}  // namespace delivery::core::application::use_cases::commands::create_order
