#include <userver/utest/utest.hpp>

#include "exceptions.hpp"
#include "weight.hpp"

namespace delivery::core::domain {

UTEST(WeightShould, BeCorrectWhenParamsIsCorrectOnCreated) {
  // Arrange

  // Act
  auto const weight = Weight{10};

  // Assert
  ASSERT_EQ(weight.GetWeight(), 10);
}

UTEST(WeightShould, ThrowExceptionWhenParamsIsInCorrectOnCreated) {
  // Arrange

  // Act & Assert
  for (auto const weight : {0, -1}) {
    ASSERT_THROW(auto const _ = Weight{weight}, ArgumentException);
  }
}

UTEST(WeightShould, BeEqualWhenAllPropertiesIsEqual) {
  // Arrange
  auto const first = Weight{10};
  auto const second = Weight{10};

  // Act
  auto const result = first == second;

  // Assert
  ASSERT_TRUE(result);
}

UTEST(WeightShould, BeNotEqualWhenAllPropertiesIsEqual) {
  // Arrange
  auto const first = Weight{10};
  auto const second = Weight{5};

  // Act
  auto const result = first == second;

  // Assert
  ASSERT_FALSE(result);
}

UTEST(WeightShould, CanCompareMoreThen) {
  // Arrange
  auto const first = Weight{10};
  auto const second = Weight{5};

  // Act
  auto const result = first > second;

  // Assert
  ASSERT_TRUE(result);
}

UTEST(WeightShould, CanCompareLessThen) {
  // Arrange
  auto const first = Weight{10};
  auto const second = Weight{5};

  // Act
  auto const result = first < second;

  // Assert
  ASSERT_FALSE(result);
}

}  // namespace delivery::core::domain
