#include "order_mock_test.hpp"

#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::order {

Order MockOrder() {
  static const auto kBasketId = userver::utils::generators::GenerateUuidV7();
  return Order::Create(BasketId{kBasketId}, Location{X{5}, Y{5}}, Weight{10});
}

}  // namespace delivery::core::domain::order
