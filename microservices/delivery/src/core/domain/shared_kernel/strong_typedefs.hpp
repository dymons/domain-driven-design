#pragma once

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain {

using CourierId =
    userver::utils::StrongTypedef<struct CourierIdTag, std::string>;

}  // namespace delivery::core::domain
