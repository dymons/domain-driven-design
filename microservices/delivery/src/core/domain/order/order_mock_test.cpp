#include "order_mock_test.hpp"

#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::order {

auto MockOrder() -> MutableSharedRef<Order> {
  return Order::Create(BasketId{userver::utils::generators::GenerateUuidV7()},
                       Location{X{5}, Y{5}}, Weight{10});
}

}  // namespace delivery::core::domain::order
