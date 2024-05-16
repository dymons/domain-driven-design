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

}  // namespace delivery::core::domain::shared_kernel
