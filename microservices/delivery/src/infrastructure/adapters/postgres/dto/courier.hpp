#pragma once

#include <string>

#include <core/domain/courier/fwd.hpp>
#include <core/domain/courier/strong_typedefs.hpp>
#include <core/domain/shared_kernel/strong_typedefs.hpp>
#include <utils/memory.hpp>

#include "location.hpp"
#include "transport.hpp"

namespace delivery::infrastructure::adapters::postgres::dto {

struct Courier final {
  core::domain::CourierId id{};
  core::domain::courier::CourierName name{};
  std::string status{};
  Transport transport{};
  Location current_location{};
};

auto Convert(SharedRef<core::domain::courier::Courier> const&) -> Courier;
auto Convert(Courier const&)
    -> MutableSharedRef<core::domain::courier::Courier>;
auto Convert(Courier&&) -> MutableSharedRef<core::domain::courier::Courier>;

}  // namespace delivery::infrastructure::adapters::postgres::dto
