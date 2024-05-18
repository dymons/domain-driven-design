#include <userver/utest/utest.hpp>

#include <vector>

#include "exceptions.hpp"
#include "location.hpp"

namespace delivery::core::domain::shared_kernel {

UTEST(LocationShould, BeCorrectWhenParamsIsCorrectOnCreated) {
  // Arrange

  for (int x = 1; x <= 10; ++x) {
    for (int y = 1; y <= 10; ++y) {
      // Act
      auto const location = Location::Create(X{x}, Y{y});

      // Assert
      EXPECT_EQ(location.GetX(), X{x});
      EXPECT_EQ(location.GetY(), Y{y});
    }
  }
}

UTEST(LocationShould, ThrowExceptionWhenParamsIsInCorrectOnCreated) {
  // Arrange
  const auto kUnexpectedLocations = std::vector{
      std::pair{0, 0},
      std::pair{11, 11},
      std::pair{11, 5},
      std::pair{5, 11},
  };

  // Act & Assert
  for (auto const location : kUnexpectedLocations) {
    EXPECT_THROW(
        auto const _ = Location::Create(X{location.first}, Y{location.second}),
        ArgumentException);
  }
}

UTEST(LocationShould, BeEqualWhenAllPropertiesIsEqual) {
  // Arrange
  auto const first = Location::Create(X{10}, Y{10});
  auto const second = Location::Create(X{10}, Y{10});

  // Act
  auto const result = first == second;

  // Assert
  EXPECT_TRUE(result);
}

UTEST(LocationShould, CanCompareMoreThen) {
  // Arrange
  auto const first = Location::Create(X{10}, Y{10});
  auto const second = Location::Create(X{5}, Y{5});

  // Act
  auto const result = first > second;

  // Assert
  EXPECT_TRUE(result);
}

UTEST(LocationShould, CanCompareMoreLess) {
  // Arrange
  auto const first = Location::Create(X{10}, Y{10});
  auto const second = Location::Create(X{5}, Y{5});

  // Act
  auto const result = first < second;

  // Assert
  EXPECT_FALSE(result);
}

UTEST(LocationShould, CanCalculateDistanceToOtherLocation) {
  // Arrange
  auto const first = Location::Create(X{10}, Y{10});
  auto const second = Location::Create(X{5}, Y{5});

  // Act
  auto const distance = first.DistanceTo(second);

  // Assert
  EXPECT_EQ(distance, Distance{10});
}

UTEST(LocationShould, HaveZeroDistanceWhenLocationIsEqual) {
  // Arrange
  auto const location = Location::Create(X{10}, Y{10});

  // Act
  auto const distance = location.DistanceTo(location);

  // Assert
  EXPECT_EQ(distance, Distance{0});
}

UTEST(LocationShould, DistanceToNotDependOrderArguments) {
  // Arrange
  auto const first = Location::Create(X{10}, Y{10});
  auto const second = Location::Create(X{5}, Y{5});

  // Act
  auto const distance1 = first.DistanceTo(second);
  auto const distance2 = second.DistanceTo(first);

  // Assert
  EXPECT_EQ(distance1, distance2);
}

}  // namespace delivery::core::domain::shared_kernel
