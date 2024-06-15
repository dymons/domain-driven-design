#pragma once

#include <utility>

namespace delivery::optional {

template <typename T, typename F>
auto map(T&& v, F&& f) -> void {
  if (v.has_value()) {
    std::forward<F>(f)(std::forward<T>(v).value());
  }
}

}  // namespace delivery::optional
