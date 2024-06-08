#pragma once

#include <userver/storages/postgres/io/user_types.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

struct Location final {
  int x{};
  int y{};
};

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Location> {
  static constexpr DBTypeName postgres_name = "location";
};
