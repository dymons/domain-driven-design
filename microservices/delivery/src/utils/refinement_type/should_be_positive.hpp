#pragma once

namespace delivery {

template <typename T>
struct ShouldBePositive final {
  auto operator()(T const& value) noexcept -> bool { return value >= 0; };
};

}  // namespace delivery
