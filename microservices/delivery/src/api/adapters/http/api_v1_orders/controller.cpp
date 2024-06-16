#include "controller.hpp"

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/storages/postgres/component.hpp>

#include <core/application/exceptions.hpp>
#include <core/application/use_cases/commands/create_order/command.hpp>
#include <core/application/use_cases/commands/create_order/handler.hpp>
#include <infrastructure/adapters/postgres/order_repository.hpp>

namespace delivery::api::api_v1_orders {

namespace {

struct Request final {
  std::string basket_id;
  std::string address;
  int weight;
};

auto Parse(const userver::formats::json::Value& request_json,
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

class Controller final : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  ~Controller() final = default;

  Controller(const userver::components::ComponentConfig& config,
             const userver::components::ComponentContext& context)
      : HttpHandlerJsonBase{config, context},
        order_repository_{
            infrastructure::adapters::postgres::MakeOrderRepository(
                context
                    .FindComponent<userver::components::Postgres>(
                        "delivery-database")
                    .GetCluster())} {}

  static constexpr std::string_view kName = "handler-api-v1-orders";

  [[nodiscard]] auto HandleRequestJsonThrow(
      const userver::server::http::HttpRequest&,
      const userver::formats::json::Value& request_json,
      userver::server::request::RequestContext&) const
      -> userver::formats::json::Value final try {
    auto request = request_json.As<Request>();

    auto command =
        application::use_cases::commands::create_order::CreateOrderCommand{
            std::move(request.basket_id), std::move(request.address),
            request.weight};

    auto const create_order_handler =
        application::use_cases::commands::create_order::CreateOrderHandler{
            order_repository_};

    create_order_handler.Handle(std::move(command));

    return {};
  } catch (const delivery::ArgumentException& ex) {
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{ex.what()});
  }

 private:
  SharedRef<core::ports::IOrderRepository> order_repository_;
};

}  // namespace

void AppendController(userver::components::ComponentList& component_list) {
  component_list.Append<Controller>();
}

}  // namespace delivery::api::api_v1_orders
