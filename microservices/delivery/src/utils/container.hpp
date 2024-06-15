#pragma once

#include <optional>

namespace delivery::container {

template <typename Container>
auto FirstOrNullopt(Container&& c)
    -> std::optional<typename Container::value_type> {
  if (not c.empty()) {
    return std::forward<Container>(c).front();
  }

  return std::nullopt;
}

}  // namespace delivery::container
