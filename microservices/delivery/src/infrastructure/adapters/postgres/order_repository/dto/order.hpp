#pragma once

#include <string>

#include <userver/storages/postgres/io/user_types.hpp>

#include <core/domain/order/fwd.hpp>
#include <core/domain/order/strong_typedefs.hpp>
#include <core/domain/shared_kernel/strong_typedefs.hpp>
#include <infrastructure/adapters/postgres/shared_kernel/dto/location.hpp>
#include <infrastructure/adapters/postgres/shared_kernel/dto/weight.hpp>
#include <utils/memory.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

struct Order final {
  core::domain::order::OrderId id{};
  std::string status{};
  std::optional<core::domain::CourierId> courier_id{};
  Location delivery_location{};
  Weight weight{};
};

auto Convert(SharedRef<core::domain::order::Order> const&) -> Order;
auto Convert(Order const&) -> MutableSharedRef<core::domain::order::Order>;
auto Convert(Order&&) -> MutableSharedRef<core::domain::order::Order>;

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Order> {
  static constexpr DBTypeName postgres_name{"delivery", "order"};
};
