#pragma once

#include <optional>

#include <core/domain/shared_kernel/location/location_mock.hpp>
#include <core/domain/shared_kernel/weight/weight_mock.hpp>

#include "order.hpp"

namespace delivery::core::domain::order {

struct MockCourierParams final {
  std::optional<std::string> basket_id{std::nullopt};
  OrderStatus status{OrderStatus::kCreated};
  std::optional<CourierId> courier_id{std::nullopt};
  Location delivery_location{MockLocation()};
  Weight weight{MockWeight()};
};

[[nodiscard]] auto MockOrder(MockCourierParams&& params = {})
    -> MutableSharedRef<Order>;

}  // namespace delivery::core::domain::order
