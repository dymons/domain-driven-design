#include <userver/utest/utest.hpp>

#include "courier_mock_test.hpp"

namespace delivery::core::domain::courier {

namespace {

UTEST(CourierShould, ThrowWhenCreateCourierWithEmptyName) {
  // Arrange
  auto courier_name = CourierName{""};

  // Act & Assert
  ASSERT_THROW(auto const _ = MockCourier({.name = courier_name}),
               ArgumentException);
}

UTEST(CourierShould, MoveToLocation) {
  // Arrange
  auto courier = MockCourier({.transport = Transport::kBicycle});

  // Act
  courier.MoveTo(Location{X{5}, Y{5}});

  // Assert
  ASSERT_EQ(courier.GetCurrentLocation(), (Location{X{3}, Y{1}}));
}

UTEST(CourierShould, CanStartWork) {
  // Arrange
  auto courier = MockCourier();

  // Act
  courier.StartWork();

  // Assert
  ASSERT_TRUE(courier.GetStatus().IsReady());
}

UTEST(CourierShould, CanStopWork) {
  // Arrange
  auto courier = MockCourier();
  courier.StartWork();

  // Act
  courier.StopWork();

  // Assert
  ASSERT_TRUE(courier.GetStatus().IsNotAvailable());
}

UTEST(CourierShould, CanCalculateTimeToLocation) {
  // Arrange
  auto courier = MockCourier();

  // Act
  auto const time = courier.CalculateTimeToPoint(Location::kMaxLocation);

  // Assert
  ASSERT_EQ(time, Time{18});
}

}  // namespace

}  // namespace delivery::core::domain::courier
