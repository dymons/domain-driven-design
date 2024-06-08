#pragma once

#include <compare>

namespace delivery::core::domain {

class Weight {
  int value_;

 public:
  Weight(int value);

  [[nodiscard]] auto GetWeight() const noexcept -> int;

  auto operator<=>(Weight const&) const -> std::strong_ordering = default;
};

}  // namespace delivery::core::domain
