#include <userver/utest/utest.hpp>

#include "courier.hpp"

namespace delivery::core::domain::courier {

namespace {

auto MockCourierName() -> CourierName {
  return CourierName{"some_courier_name"};
}

auto MockTransport() -> Transport { return Transport::kPedestrian; }

UTEST(CourierShould, BeConstructibleWithRequiredProperties) {
  // Arrange

  // Act
  auto const courier = Courier::Create(MockCourierName(), MockTransport());

  // Assert
  ASSERT_TRUE(courier.GetStatus().IsNotAvailable());
  ASSERT_EQ(courier.GetName(), MockCourierName());
  ASSERT_EQ(courier.GetCurrentLocation(), Location::kMinLocation);
}

UTEST(CourierShould, ThrowWhenCreateCourierWithEmptyName) {
  // Arrange
  auto courier_name = CourierName{""};

  // Act & Assert
  ASSERT_THROW(auto const _ = Courier::Create(courier_name, MockTransport()),
               ArgumentException);
}

UTEST(CourierShould, MoveToLocation) {
  // Arrange
  auto courier = Courier::Create(MockCourierName(), Transport::kBicycle);

  // Act
  courier.MoveTo(Location{X{5}, Y{5}});

  // Assert
  ASSERT_EQ(courier.GetCurrentLocation(), (Location{X{3}, Y{1}}));
}

UTEST(CourierShould, CanStartWork) {
  // Arrange
  auto courier = Courier::Create(MockCourierName(), MockTransport());

  // Act
  courier.StartWork();

  // Assert
  ASSERT_TRUE(courier.GetStatus().IsReady());
}

UTEST(CourierShould, CanStopWork) {
  // Arrange
  auto courier = Courier::Create(MockCourierName(), MockTransport());
  courier.StartWork();

  // Act
  courier.StopWork();

  // Assert
  ASSERT_TRUE(courier.GetStatus().IsNotAvailable());
}

UTEST(CourierShould, CanCalculateTimeToLocation) {
  // Arrange
  auto courier = Courier::Create(MockCourierName(), MockTransport());

  // Act
  auto const time = courier.CalculateTimeToPoint(Location::kMaxLocation);

  // Assert
  ASSERT_EQ(time, Time{18});
}

}  // namespace

}  // namespace delivery::core::domain::courier
