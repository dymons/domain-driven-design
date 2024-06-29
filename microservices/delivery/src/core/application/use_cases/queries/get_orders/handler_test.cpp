#include <userver/utest/utest.hpp>

#include <core/domain/order/order_mock_test.hpp>
#include <core/ports/order_repository/repository_mock_test.hpp>

#include "handler.hpp"

namespace delivery::core::application::use_cases::queries::get_orders {

namespace {

class CreateOrderHandlerShould : public ::testing::Test {
 private:
  SharedRef<core::ports::IOrderRepository> mock_order_repository_ =
      core::ports::MockOrderRepository({
          core::domain::order::MockOrder(),
      });

 protected:
  SharedRef<IGetOrdersHandler> get_orders_handler_ =
      MakeGetOrdersHandler(mock_order_repository_);
};

UTEST(GetOrdersHandlerShould, ReturnOrders) {}

}  // namespace

}  // namespace delivery::core::application::use_cases::queries::get_orders
