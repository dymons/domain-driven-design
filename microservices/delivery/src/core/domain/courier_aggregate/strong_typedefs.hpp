#pragma once

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain::courier_aggregate {

using CourierId =
    userver::utils::StrongTypedef<struct CourierIdTag, std::string>;
using CourierName =
    userver::utils::StrongTypedef<struct CourierNameTag, std::string>;
using Duration = userver::utils::StrongTypedef<struct DurationTag, int>;

}  // namespace delivery::core::domain::courier_aggregate
