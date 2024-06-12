#pragma once

#include "userver/utils/strong_typedef.hpp"

namespace delivery {

class RuntimeRefinementError final : public std::exception {
 public:
  auto what() const noexcept -> const char* final {
    return "Runtime refinement type check";
  }
};

template <class Tag, class T, template <typename> typename... Refinement>
class RefinementType final : public userver::utils::StrongTypedef<Tag, T> {
  using Base = userver::utils::StrongTypedef<Tag, T>;

 public:
  template <typename... Args,
            typename = std::enable_if_t<std::is_constructible_v<T, Args...>>>
  explicit constexpr RefinementType(Args&&... args) noexcept(
      noexcept(T(std::forward<Args>(args)...)))
      : Base(std::forward<Args>(args)...) {
    const auto is_refinementable =
        (... && Refinement<T>{}(Base::GetUnderlying()));
    if (not is_refinementable) {
      throw RuntimeRefinementError{};
    }
  }
};

}  // namespace delivery
