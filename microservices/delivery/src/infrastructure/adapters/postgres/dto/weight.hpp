#pragma once

#include <userver/storages/postgres/io/user_types.hpp>

namespace delivery::core::domain {
class Weight;
}  // namespace delivery::core::domain

namespace delivery::infrastructure::adapters::postgres::dto {

struct Weight final {
  int value{};
};

auto Convert(core::domain::Weight const&) -> Weight;
auto Convert(Weight const&) -> core::domain::Weight;

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Weight> {
  static constexpr DBTypeName postgres_name = "weight";
};
