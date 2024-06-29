#include <userver/utest/utest.hpp>

#include <core/domain/order/order_mock_test.hpp>
#include <core/ports/order_repository/repository_mock_test.hpp>

#include "handler.hpp"

namespace delivery::core::application::use_cases::queries::get_orders {

namespace {

auto const kBasketIdOne = std::string{"basket_id-1"};
auto const kBasketIdTwo = std::string{"basket_id-2"};
auto const kBasketIdThree = std::string{"basket_id-3"};

class GetOrdersHandlerShould : public ::testing::Test {
 public:
  ~GetOrdersHandlerShould() override = default;

 private:
  SharedRef<core::ports::IOrderRepository> mock_order_repository_ =
      core::ports::MockOrderRepository({
          core::domain::order::MockOrder(
              {.basket_id = kBasketIdOne,
               .delivery_location =
                   core::domain::Location{core::domain::X{1},
                                          core::domain::Y{1}}}),
          core::domain::order::MockOrder(
              {.basket_id = kBasketIdTwo,
               .delivery_location =
                   core::domain::Location{core::domain::X{2},
                                          core::domain::Y{2}}}),
          core::domain::order::MockOrder(
              {.basket_id = kBasketIdThree,
               .delivery_location =
                   core::domain::Location{core::domain::X{3},
                                          core::domain::Y{3}}}),
      });

 protected:
  SharedRef<IGetOrdersHandler> get_orders_handler_ =
      MakeGetOrdersHandler(mock_order_repository_);
};

UTEST_F(GetOrdersHandlerShould, ReturnOrders) {
  // Arrange
  auto query = GetOrdersQuery{};

  ASSERT_NO_THROW(([&, this]() {
    // Act
    auto const response = get_orders_handler_->Handle(std::move(query));

    // Assert
    ASSERT_TRUE(std::holds_alternative<Response200>(response));

    auto orders = std::get<Response200>(response).orders;
    auto expected_orders =
        std::vector<Order>{Order{kBasketIdOne, Location{1, 1}},
                           Order{kBasketIdTwo, Location{2, 2}},
                           Order{kBasketIdThree, Location{3, 3}}};

    std::ranges::sort(orders);
    std::ranges::sort(expected_orders);

    ASSERT_EQ(orders, expected_orders);
  }()));
}

}  // namespace

}  // namespace delivery::core::application::use_cases::queries::get_orders
