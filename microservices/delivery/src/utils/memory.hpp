#pragma once

#include <userver/utils/not_null.hpp>

namespace delivery {

template <typename T>
using SharedRef = userver::utils::SharedRef<const T>;

template <typename T>
using MutableSharedRef = userver::utils::SharedRef<T>;

template <typename U, typename... Args>
SharedRef<U> MakeSharedRef(Args&&... args) {
  return SharedRef<U>{std::make_shared<U>(std::forward<Args>(args)...)};
}

template <typename U, typename... Args>
MutableSharedRef<U> MakeMutableSharedRef(Args&&... args) {
  return MutableSharedRef<U>{std::make_shared<U>(std::forward<Args>(args)...)};
}

}  // namespace delivery
