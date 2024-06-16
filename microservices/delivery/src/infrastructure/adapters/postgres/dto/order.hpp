#pragma once

#include <string>

#include <userver/storages/postgres/io/user_types.hpp>

#include <core/domain/order/strong_typedefs.hpp>
#include <utils/memory.hpp>

#include "location.hpp"
#include "weight.hpp"

namespace delivery::core::domain::order {
class Order;
}  // namespace delivery::core::domain::order

namespace delivery::infrastructure::adapters::postgres::dto {

struct Order final {
  core::domain::order::OrderId id{};
  std::string status{};
  std::optional<core::domain::order::CourierId> courier_id{};
  Location delivery_location{};
  Weight weight{};
};

auto Convert(SharedRef<core::domain::order::Order> const&) -> Order;
auto Convert(Order const&) -> MutableSharedRef<core::domain::order::Order>;

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Order> {
  static constexpr DBTypeName postgres_name{"delivery", "order"};
};
