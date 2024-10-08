#pragma once

#include <string>

#include <userver/storages/postgres/io/user_types.hpp>

#include <core/domain/courier/fwd.hpp>

namespace delivery::infrastructure::adapters::postgres::dto {

struct Transport {
  int id{};
  std::string name{};
  int speed{};
  int capacity{};
};

auto Convert(core::domain::courier::Transport const&) -> Transport;
auto Convert(Transport const&) -> core::domain::courier::Transport;
auto Convert(Transport&&) -> core::domain::courier::Transport;

}  // namespace delivery::infrastructure::adapters::postgres::dto

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    ::delivery::infrastructure::adapters::postgres::dto::Transport> {
  static constexpr DBTypeName postgres_name{"delivery", "transport"};
};
