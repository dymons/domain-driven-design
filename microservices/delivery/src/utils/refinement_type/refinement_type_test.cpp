#include <userver/utest/utest.hpp>

#include <string>

#include "refinement_type.hpp"

namespace delivery {

namespace {

UTEST(RefinementTypeShould, BeConstructable) {
  using RegisterValue = RefinementType<struct RegisterValueTag, int>;
  [[maybe_unused]] auto value = RegisterValue{1};
}

UTEST(RefinementTypeShould, BeConstructableWithRefinements) {
  struct NotEmpty final {
    auto operator()(std::string const& value) noexcept -> bool {
      return not value.empty();
    };
  };

  using Address = RefinementType<struct AddressTag, std::string, NotEmpty>;
  ASSERT_THROW(Address{""}, RuntimeRefinementError);

  [[maybe_unused]] auto value = Address{"Address"};
}

}  // namespace

}  // namespace delivery
