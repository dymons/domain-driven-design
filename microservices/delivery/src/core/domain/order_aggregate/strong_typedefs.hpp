#pragma once

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain::order_aggregate {

// clang-format off
using OrderId = userver::utils::StrongTypedef<struct OrderIdTag, std::string>;
using BasketId = userver::utils::StrongTypedef<struct BasketIdTag, std::string>;
using CourierId = userver::utils::StrongTypedef<struct CourierIdTag, std::string>;
// clang-format on

}  // namespace delivery::core::domain::order_aggregate
