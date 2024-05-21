#include <userver/utest/utest.hpp>

#include "courier.hpp"

namespace delivery::core::domain::courier_aggregate {

namespace {

auto MockCourierName() -> CourierName {
  return CourierName{"some_courier_name"};
}

auto MockTransport() -> Transport { return Transport{}; }

}  // namespace

UTEST(CourierShould, BeConstructibleWithRequiredProperties) {
  // Arrange

  // Act
  auto const courier = Courier::Create(MockCourierName(), MockTransport());

  // Assert
  EXPECT_EQ(courier.GetStatus(), CourierStatus::NotAvailable);
  EXPECT_EQ(courier.GetName(), MockCourierName());
  EXPECT_EQ(courier.GetCurrentLocation(),
            shared_kernel::Location::Create(shared_kernel::X{1},
                                            shared_kernel::Y{1}));
}

}  // namespace delivery::core::domain::courier_aggregate
