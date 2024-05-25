#include <userver/utest/utest.hpp>

#include "courier.hpp"

namespace delivery::core::domain::courier_aggregate {

namespace {

auto MockCourierName() -> CourierName {
  return CourierName{"some_courier_name"};
}

auto MockTransport() -> Transport { return Transport::kPedestrian; }

}  // namespace

UTEST(CourierShould, BeConstructibleWithRequiredProperties) {
  // Arrange

  // Act
  auto const courier = Courier::Create(MockCourierName(), MockTransport());

  // Assert
  EXPECT_EQ(courier.GetStatus(), CourierStatus::NotAvailable);
  EXPECT_EQ(courier.GetName(), MockCourierName());
  EXPECT_EQ(courier.GetCurrentLocation(),
            shared_kernel::Location::kMinLocation);
}

UTEST(CourierShould, ThrowWhenCreateCourierWithEmptyName) {
  // Arrange
  auto courier_name = CourierName{""};

  // Act & Assert
  EXPECT_THROW(auto const _ = Courier::Create(courier_name, MockTransport()),
               ArgumentException);
}

UTEST(CourierShould, MoveToLocation) {
  // Arrange
  auto courier = Courier::Create(MockCourierName(), Transport::kBicycle);

  // Act
  courier.MoveTo(shared_kernel::Location::Create(shared_kernel::X{5},
                                                 shared_kernel::Y{5}));

  // Assert
  EXPECT_EQ(courier.GetCurrentLocation(),
            shared_kernel::Location::Create(shared_kernel::X{3},
                                            shared_kernel::Y{1}));
}

}  // namespace delivery::core::domain::courier_aggregate
