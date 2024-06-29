#include "order_mock_test.hpp"

#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::order {

auto MockOrder(MockCourierParams params) -> MutableSharedRef<Order> {
  return Order::Create(BasketId{params.basket_id.value_or(
                           userver::utils::generators::GenerateUuidV7())},
                       params.delivery_location, params.weight);
}

}  // namespace delivery::core::domain::order
