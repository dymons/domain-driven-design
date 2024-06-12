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

UTEST(RefinementTypeShould, BeCopyable) {
  using Address = RefinementType<struct AddressTag, std::string>;
  auto const address = Address{"Address"};

  // NOLINTNEXTLINE(*-unnecessary-copy-initialization)
  auto const copy_address = address;

  ASSERT_EQ(address, copy_address);
}

UTEST(RefinementTypeShould, BeMovable) {
  struct NotEmpty final {
    auto operator()(std::string const& value) noexcept -> bool {
      return not value.empty();
    };
  };

  using Address = RefinementType<struct AddressTag, std::string, NotEmpty>;
  auto address = Address{"Address"};

  // NOLINTNEXTLINE(*-unnecessary-copy-initialization)
  auto const move_address = std::move(address);

  ASSERT_TRUE(address.empty());  // NOLINT(*-use-after-move)
  ASSERT_EQ(move_address, Address{"Address"});
}

}  // namespace

}  // namespace delivery
