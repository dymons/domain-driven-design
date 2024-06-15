#pragma once

#include <utility>

namespace delivery::optional {

template <typename T, typename F>
void map(T&& v, F&& f) {
  if (v.has_value()) {
    f(std::forward<T>(v).value());
  }
}

}  // namespace delivery::optional
