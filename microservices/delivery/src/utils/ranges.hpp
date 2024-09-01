#pragma once

#include <algorithm>
#include <ranges>

namespace delivery::ranges {

// TODO (dymons) Wait support std::ranges::to at C++23

template <template <class...> class ConT>
struct to {
  template <std::ranges::range R>
  auto operator()(R&& rng) const {
    auto result = ConT<std::ranges::range_value_t<R>>{};
    std::ranges::copy(rng, std::back_inserter(result));
    return result;
  }

  template <std::ranges::range R>
  friend decltype(auto) operator|(R&& rng, to fun) {
    return fun(std::forward<R>(rng));
  }
};

}  // namespace delivery::ranges
