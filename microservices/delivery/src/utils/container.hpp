#pragma once

#include <optional>

namespace delivery::container {

template <typename Container>
[[nodiscard]] auto FirstOrNullopt(Container&& c)
    -> std::optional<typename Container::value_type> {
  // TODO (dymons) Support https://en.cppreference.com/w/cpp/container
  if (not c.empty()) {
    return std::forward<Container>(c).front();
  }

  return std::nullopt;
}

}  // namespace delivery::container
