#pragma once

#include <userver/utils/strong_typedef.hpp>

namespace delivery::core::domain::order {

using OrderId = userver::utils::StrongTypedef<struct OrderIdTag, std::string>;
using BasketId = userver::utils::StrongTypedef<struct BasketIdTag, std::string>;
using CourierId = userver::utils::StrongTypedef<struct CourierTag, std::string>;

}  // namespace delivery::core::domain::order
