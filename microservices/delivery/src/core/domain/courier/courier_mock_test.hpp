#pragma once

#include "courier.hpp"
#include "exceptions.hpp"

namespace delivery::core::domain::courier {

struct MockCourierParams final {
  CourierName name = CourierName{"CourierName"};
  Transport transport = Transport::kPedestrian;
};

[[nodiscard]] auto MockCourier(MockCourierParams params = {})
    -> MutableSharedRef<Courier>;

}  // namespace delivery::core::domain::courier
