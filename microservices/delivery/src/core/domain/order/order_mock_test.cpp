#include "order_mock_test.hpp"

#include <userver/utils/uuid7.hpp>

namespace delivery::core::domain::order {

auto MockOrder(MockCourierParams&& params) -> MutableSharedRef<Order> {
  return Order::Hydrate(
      OrderId{std::move(params.basket_id)
                  .value_or(userver::utils::generators::GenerateUuidV7())},
      params.status, std::move(params.courier_id), params.delivery_location,
      params.weight);
}

}  // namespace delivery::core::domain::order
