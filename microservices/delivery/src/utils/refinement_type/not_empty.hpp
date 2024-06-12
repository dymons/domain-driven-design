#pragma once

#include <concepts>

namespace delivery {

template <typename T>
concept HasEmptyMethod = requires(T&& t) {
  { t.empty() } -> std::same_as<bool>;
};

template <HasEmptyMethod T>
struct NotEmpty final {
  auto operator()(T const& value) noexcept -> bool {
    return not value.empty();
  };
};

}  // namespace delivery
