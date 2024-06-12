#pragma once

#include <optional>

namespace delivery::optional {

template <typename Container>
auto FirstOrNullopt(Container&& c)
    -> std::optional<typename Container::value_type> {
  if (c.empty()) {
    return std::nullopt;
  }

  return c.front();
}

}  // namespace delivery::optional
