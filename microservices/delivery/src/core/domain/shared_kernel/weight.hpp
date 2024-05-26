#pragma once

#include <compare>

namespace delivery::core::domain::shared_kernel {

class Weight {
  int value_;

  // Constructors

  explicit Weight(int value) : value_(value) {}

 public:
  [[nodiscard]] static auto Create(int value) -> Weight;

  // Observers

  [[nodiscard]] auto GetWeight() const noexcept -> int { return value_; }

  auto operator<=>(Weight const&) const -> std::strong_ordering = default;
};

}  // namespace delivery::core::domain::shared_kernel
