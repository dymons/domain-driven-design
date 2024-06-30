#include "request.hpp"

#include <userver/formats/json/value.hpp>

namespace delivery::api::adapters::http::api_v1_orders_active {

auto Parse(userver::formats::json::Value const&,
           userver::formats::parse::To<Request>) -> Request {
  return {};
}

}  // namespace delivery::api::adapters::http::api_v1_orders_active
