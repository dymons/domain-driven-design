#pragma once

#include <userver/storages/postgres/io/user_types.hpp>

namespace delivery::core::domain {
class Location;
}  // namespace delivery::core::domain

namespace delivery::infrastructure::adapters::postgres::dto {

struct Location final {
  int x{};
  int y{};
};

auto Convert(core::domain::Location const&) -> Location;
auto Convert(Location const&) -> core::domain::Location;

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Location> {
  static constexpr DBTypeName postgres_name = "location";
};
