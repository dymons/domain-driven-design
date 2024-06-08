#pragma once

#include <string>

#include <userver/storages/postgres/io/user_types.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

struct Transport {
  int id{};
  std::string name{};
  int speed{};
  int capacity{};
};

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Transport> {
  static constexpr DBTypeName postgres_name = "transport";
};
