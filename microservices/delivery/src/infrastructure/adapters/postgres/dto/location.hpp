#pragma once

#include <userver/storages/postgres/io/user_types.hpp>

namespace delivery::core::domain::shared_kernel {
class Location;
}  // namespace delivery::core::domain::shared_kernel

namespace delivery::infrastructure::adapters::postgres::dto {

struct Location final {
  int x{};
  int y{};
};

auto Convert(core::domain::shared_kernel::Location const&) -> Location;
auto Convert(Location const&) -> core::domain::shared_kernel::Location;

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Location> {
  static constexpr DBTypeName postgres_name = "location";
};
