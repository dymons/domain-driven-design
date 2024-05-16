#include "weight.hpp"

#include <userver/utest/utest.hpp>

namespace delivery::core::domain::shared_kernel {

UTEST(WeightShould, BeCorrectWhenParamsIsCorrectOnCreated) {
  // Arrange

  // Act
  auto const weight = Weight::Create(10);

  // Assert
  EXPECT_EQ(weight.GetWeight(), 10);
}

UTEST(WeightShould, BeEqualWhenAllPropertiesIsEqual) {
  // Arrange
  auto const first = Weight::Create(10);
  auto const second = Weight::Create(10);

  // Act
  auto const result = first == second;

  // Assert
  EXPECT_TRUE(result);
}

UTEST(WeightShould, BeNotEqualWhenAllPropertiesIsEqual) {
  // Arrange
  auto const first = Weight::Create(10);
  auto const second = Weight::Create(5);

  // Act
  auto const result = first == second;

  // Assert
  EXPECT_FALSE(result);
}

UTEST(WeightShould, CanCompareMoreThen) {
  // Arrange
  auto const first = Weight::Create(10);
  auto const second = Weight::Create(5);

  // Act
  auto const result = first > second;

  // Assert
  EXPECT_TRUE(result);
}

UTEST(WeightShould, CanCompareLessThen) {
  // Arrange
  auto const first = Weight::Create(10);
  auto const second = Weight::Create(5);

  // Act
  auto const result = first < second;

  // Assert
  EXPECT_FALSE(result);
}

}  // namespace delivery::core::domain::shared_kernel
