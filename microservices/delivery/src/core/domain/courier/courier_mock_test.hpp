#pragma once

#include "courier.hpp"
#include "exceptions.hpp"

namespace delivery::core::domain::courier {

struct MockCourierParams final {
  CourierName name = CourierName{"some_courier_name"};
  Transport transport = Transport::kPedestrian;
};

[[nodiscard]] auto MockCourier(MockCourierParams params = {}) -> Courier;

}  // namespace delivery::core::domain::courier
