#include <userver/utest/utest.hpp>

#include <core/domain/order/order_mock.hpp>
#include <core/ports/order_repository/repository_mock.hpp>

#include "handler.hpp"
#include "ihandler.hpp"
#include "query.hpp"
#include "response.hpp"

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

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
                   core::domain::Location{core::domain::XCoord{1},
                                          core::domain::YCoord{1}}}),
          core::domain::order::MockOrder(
              {.basket_id = kBasketIdTwo,
               .delivery_location =
                   core::domain::Location{core::domain::XCoord{2},
                                          core::domain::YCoord{2}}}),
          core::domain::order::MockOrder(
              {.basket_id = kBasketIdThree,
               .delivery_location =
                   core::domain::Location{core::domain::XCoord{3},
                                          core::domain::YCoord{3}}}),
          core::domain::order::MockOrder(
              {.basket_id = kBasketIdThree,
               .status = core::domain::order::OrderStatus::kCompleted,
               .delivery_location =
                   core::domain::Location{core::domain::XCoord{3},
                                          core::domain::YCoord{3}}}),
      });

 protected:
  SharedRef<IGetActiveOrdersHandler> get_orders_handler_ =
      MakeGetActiveOrdersHandler(mock_order_repository_);
};

UTEST_F(GetOrdersHandlerShould, ReturnOrders) {
  // Arrange
  auto query = GetActiveOrdersQuery{};

  ASSERT_NO_THROW(([&, this]() {
    // Act
    auto orders = get_orders_handler_->Handle(std::move(query));

    // Assert
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

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
