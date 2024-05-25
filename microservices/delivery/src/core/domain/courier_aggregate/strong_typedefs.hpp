#pragma once

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain::courier_aggregate {

// TODO (dymons) Use libraries to work with Duration/Speed/Time
// TODO (dymons) Use refinement types

using CourierId =
    userver::utils::StrongTypedef<struct CourierIdTag, std::string>;
using CourierName =
    userver::utils::StrongTypedef<struct CourierNameTag, std::string>;

using Duration = userver::utils::StrongTypedef<struct DurationTag, int>;
using Speed = userver::utils::StrongTypedef<struct SpeedTag, int>;
using Time = userver::utils::StrongTypedef<struct TimeTag, double>;

using TransportId =
    userver::utils::StrongTypedef<struct TransportIdTag, int>;
using TransportName =
    userver::utils::StrongTypedef<struct TransportNameTag, std::string>;

}  // namespace delivery::core::domain::courier_aggregate
