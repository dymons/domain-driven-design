#pragma once

#include <utility>

namespace delivery::core::domain::shared_kernel {

class Weight {
  int weight_;

  explicit Weight(int weight) : weight_(weight) {}

 public:
  static auto Create(int weight) -> Weight;

  template <typename Self>
  constexpr decltype(auto) GetWeight(this Self&& self) {
    return std::forward<Self>(self).weight_;
  }

  constexpr auto operator<=>(Weight const&) const = default;
};

}  // namespace delivery::core::domain::shared_kernel
