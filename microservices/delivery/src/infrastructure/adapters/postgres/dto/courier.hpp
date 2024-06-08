#pragma once

#include <string>

#include "location.hpp"
#include "transport.hpp"

namespace delivery::core::domain::courier {
class Courier;
}  // namespace delivery::core::domain::courier

namespace delivery::infrastructure::adapters::postgres::dto {

struct Courier final {
  std::string id{};
  std::string name{};
  std::string status{};
  Transport transport{};
  Location current_location{};
};

auto Convert(core::domain::courier::Courier const&) -> Courier;
auto Convert(Courier const&) -> core::domain::courier::Courier;

}  // namespace delivery::infrastructure::adapters::postgres::dto
