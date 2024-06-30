#pragma once

#include <userver/components/component_list.hpp>

namespace delivery::api::adapters::http::api_v1_couriers {

auto AppendController(userver::components::ComponentList&) -> void;

}  // namespace delivery::api::adapters::http::api_v1_couriers
