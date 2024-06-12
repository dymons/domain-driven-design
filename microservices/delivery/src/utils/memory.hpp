#pragma once

#include <userver/utils/not_null.hpp>

namespace delivery {

template <typename T>
using SharedRef = userver::utils::SharedRef<const T>;

}  // namespace delivery
