#include <userver/utest/utest.hpp>

#include <core/application/use_cases/queries/get_orders/handler.hpp>
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
  SharedRef<ICreateOrderHandler> create_order_handler_ =
      MakeCreateOrderHandler(mock_order_repository_);
  SharedRef<queries::get_orders::IGetOrdersHandler> get_orders_handler_ =
      queries::get_orders::MakeGetOrdersHandler(mock_order_repository_);

  auto GetOrders() -> std::vector<queries::get_orders::Order> {
    auto r = get_orders_handler_->Handle(queries::get_orders::GetOrdersQuery{});
    return std::get<queries::get_orders::Response200>(std::move(r)).orders;
  }
};

UTEST_F(CreateOrderHandlerShould, CreateOrder) {
  // Arrange
  auto command = CreateOrderCommand{kBasketId, kAddress, kWeight};

  // Act
  ASSERT_NO_THROW(create_order_handler_->Handle(std::move(command)));

  // Assert
  auto const orders = GetOrders();
  ASSERT_EQ(orders.size(), 1);
}

UTEST_F(CreateOrderHandlerShould, IdempotencyCreateOrder) {
  // Arrange
  auto const command = CreateOrderCommand{kBasketId, kAddress, kWeight};

  // Act
  ASSERT_NO_THROW(create_order_handler_->Handle(CreateOrderCommand{command}));
  ASSERT_NO_THROW(create_order_handler_->Handle(CreateOrderCommand{command}));

  // Assert
  auto const orders = GetOrders();
  ASSERT_EQ(orders.size(), 1);
}

}  // namespace

}  // namespace delivery::core::application::use_cases::commands::create_order
