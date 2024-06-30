#include "request.hpp"

#include <optional>

#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/server/handlers/exceptions.hpp>

namespace delivery::api::adapters::http::api_v1_couriers {

auto Parse(userver::formats::json::Value const&,
           userver::formats::parse::To<Request>) -> Request {
  return {};
}

}  // namespace delivery::api::adapters::http::api_v1_couriers
