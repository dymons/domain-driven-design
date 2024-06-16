#include "request.hpp"

#include <optional>

#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/server/handlers/exceptions.hpp>

namespace delivery::api::adapters::http::api_v1_orders {

auto Parse(userver::formats::json::Value const& request_json,
           userver::formats::parse::To<Request>) -> Request {
  auto basket_id = request_json["basket_id"].As<std::optional<std::string>>();
  if (not basket_id.has_value()) {
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{
            "No 'basket_id' query argument"});
  }

  auto address = request_json["address"].As<std::optional<std::string>>();
  if (not address.has_value()) {
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{"No 'address' query argument"});
  }

  const auto weight = request_json["weight"].As<std::optional<int>>();
  if (not weight.has_value()) {
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{"No 'weight' query argument"});
  }

  return {
      .basket_id = std::move(basket_id).value(),
      .address = std::move(address).value(),
      .weight = weight.value(),
  };
}

}  // namespace delivery::api::adapters::http::api_v1_orders
