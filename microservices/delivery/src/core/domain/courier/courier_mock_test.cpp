#include "courier_mock_test.hpp"

namespace delivery::core::domain::courier {

auto MockCourier(MockCourierParams params) -> MutableSharedRef<Courier> {
  return Courier::Create(std::move(params.name), std::move(params.transport));
};

}  // namespace delivery::core::domain::courier
