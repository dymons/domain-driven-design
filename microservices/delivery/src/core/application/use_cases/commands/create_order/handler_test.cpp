#include <userver/utest/utest.hpp>

#include <core/application/use_cases/queries/get_active_orders/handler.hpp>
#include <core/domain/order/order.hpp>
#include <core/ports/order_repository/repository_mock_test.hpp>

#include "handler.hpp"

namespace delivery::core::application::use_cases::commands::create_order {

namespace {

auto const kBasketId = std::string{"basket_id"};
auto const kAddress = std::string{"address"};
auto const kWeight = int{5};

class CreateOrderHandlerShould : public ::testing::Test {
 public:
  ~CreateOrderHandlerShould() override = default;

 private:
  SharedRef<core::ports::IOrderRepository> mock_order_repository_ =
      core::ports::MockOrderRepository();

 protected:
  SharedRef<ICreateOrderHandler> create_order_handler_ =
      MakeCreateOrderHandler(mock_order_repository_);
  SharedRef<queries::get_active_orders::IGetActiveOrdersHandler>
      get_orders_handler_ =
          queries::get_active_orders::MakeGetActiveOrdersHandler(
              mock_order_repository_);

  auto GetActiveOrders() -> std::vector<queries::get_active_orders::Order> {
    auto response = get_orders_handler_->Handle(
        queries::get_active_orders::GetActiveOrdersQuery{});
    return std::get<queries::get_active_orders::Response200>(
               std::move(response))
        .orders;
  }
};

UTEST_F(CreateOrderHandlerShould, CreateOrder) {
  // Arrange
  auto command = CreateOrderCommand{kBasketId, kAddress, kWeight};

  // Act
  ASSERT_NO_THROW(create_order_handler_->Handle(std::move(command)));

  // Assert
  auto const orders = GetActiveOrders();
  ASSERT_EQ(orders.size(), 1);

  auto const& order = orders.front();
  ASSERT_EQ(order.GetId(), kBasketId);
  ASSERT_EQ(order.GetLocation(), (queries::get_active_orders::Location{1, 1}));
}

UTEST_F(CreateOrderHandlerShould, IdempotencyCreateOrder) {
  // Arrange
  auto const command = CreateOrderCommand{kBasketId, kAddress, kWeight};

  // Act
  ASSERT_NO_THROW(create_order_handler_->Handle(CreateOrderCommand{command}));
  ASSERT_NO_THROW(create_order_handler_->Handle(CreateOrderCommand{command}));

  // Assert
  auto const orders = GetActiveOrders();
  ASSERT_EQ(orders.size(), 1);
}

}  // namespace

}  // namespace delivery::core::application::use_cases::commands::create_order
