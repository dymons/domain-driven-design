#include "order_mock_test.hpp"

#include <userver/utils/uuid7.hpp>

#include <core/domain/shared_kernel/location/location_mock_test.hpp>
#include <core/domain/shared_kernel/weight/weight_mock_test.hpp>

namespace delivery::core::domain::order {

auto MockOrder() -> MutableSharedRef<Order> {
  return Order::Create(BasketId{userver::utils::generators::GenerateUuidV7()},
                       MockLocation(), MockWeight());
}

}  // namespace delivery::core::domain::order
