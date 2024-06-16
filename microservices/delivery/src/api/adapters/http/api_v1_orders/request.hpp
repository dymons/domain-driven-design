#pragma once

#include <string>

#include <userver/formats/parse/to.hpp>

namespace userver::formats::json {
class Value;
}  // namespace userver::formats::json

namespace delivery::api::adapters::http::api_v1_orders {

struct Request final {
  std::string basket_id;
  std::string address;
  int weight;
};

[[nodiscard]] auto Parse(userver::formats::json::Value const&,
                         userver::formats::parse::To<Request>) -> Request;

}  // namespace delivery::api::adapters::http::api_v1_orders
