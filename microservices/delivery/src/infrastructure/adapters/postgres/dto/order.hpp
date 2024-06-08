#pragma once

#include <string>

#include <core/domain/courier/strong_typedefs.hpp>
#include <core/domain/order/strong_typedefs.hpp>

#include "location.hpp"
#include "weight.hpp"

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::infrastructure::adapters::postgres::dto {

struct Order final {
  core::domain::order::OrderId id{};
  std::string status{};
  std::optional<core::domain::courier::CourierId> courier_id{};
  Location delivery_location{};
  Weight weight{};
};

auto Convert(core::domain::order::Order const&) -> Order;
auto Convert(Order const&) -> core::domain::order::Order;

}  // namespace delivery::infrastructure::adapters::postgres::dto
