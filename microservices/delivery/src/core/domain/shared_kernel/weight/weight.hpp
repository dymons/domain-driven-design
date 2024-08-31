#pragma once

#include <compare>

namespace delivery::core::domain {

class Weight final {
  int value_;

 public:
  // Constructors

  Weight(int value);

  // Observers

  [[nodiscard]] auto GetWeight() const noexcept -> int;

  auto operator<=>(Weight const&) const = default;
};

}  // namespace delivery::core::domain
