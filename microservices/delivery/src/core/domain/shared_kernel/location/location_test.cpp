#include <userver/utest/utest.hpp>

#include <vector>

#include <core/domain/shared_kernel/exceptions.hpp>
#include "location.hpp"

namespace delivery::core::domain {

namespace {

UTEST(LocationShould, BeCorrectWhenParamsIsCorrectOnCreated) {
  // Arrange

  for (int x = 1; x <= 10; ++x) {
    for (int y = 1; y <= 10; ++y) {
      // Act
      auto const location = Location{XCoord{x}, YCoord{y}};

      // Assert
      ASSERT_EQ(location.GetX(), XCoord{x});
      ASSERT_EQ(location.GetY(), YCoord{y});
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
    ASSERT_THROW((Location{XCoord{location.first}, YCoord{location.second}}),
                 ArgumentException);
  }
}

UTEST(LocationShould, BeEqualWhenAllPropertiesIsEqual) {
  // Arrange
  auto const first = Location{XCoord{10}, YCoord{10}};
  auto const second = Location{XCoord{10}, YCoord{10}};

  // Act
  auto const result = first == second;

  // Assert
  ASSERT_TRUE(result);
}

UTEST(LocationShould, CanCompareMoreThen) {
  // Arrange
  auto const first = Location{XCoord{10}, YCoord{10}};
  auto const second = Location{XCoord{5}, YCoord{5}};

  // Act
  auto const result = first > second;

  // Assert
  ASSERT_TRUE(result);
}

UTEST(LocationShould, CanCompareMoreLess) {
  // Arrange
  auto const first = Location{XCoord{10}, YCoord{10}};
  auto const second = Location{XCoord{5}, YCoord{5}};

  // Act
  auto const result = first < second;

  // Assert
  ASSERT_FALSE(result);
}

UTEST(LocationShould, CanCalculateDistanceToOtherLocation) {
  // Arrange
  auto const first = Location{XCoord{10}, YCoord{10}};
  auto const second = Location{XCoord{5}, YCoord{5}};

  // Act
  auto const distance = first.DistanceTo(second);

  // Assert
  ASSERT_EQ(distance, Distance{10});
}

UTEST(LocationShould, HaveZeroDistanceWhenLocationIsEqual) {
  // Arrange
  auto const location = Location{XCoord{10}, YCoord{10}};

  // Act
  auto const distance = location.DistanceTo(location);

  // Assert
  ASSERT_EQ(distance, Distance{0});
}

UTEST(LocationShould, DistanceToNotDependOrderArguments) {
  // Arrange
  auto const first = Location{XCoord{10}, YCoord{10}};
  auto const second = Location{XCoord{5}, YCoord{5}};

  // Act
  auto const distance1 = first.DistanceTo(second);
  auto const distance2 = second.DistanceTo(first);

  // Assert
  ASSERT_EQ(distance1, distance2);
}

}  // namespace

}  // namespace delivery::core::domain
