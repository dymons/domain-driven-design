#include "controller.hpp"

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/storages/postgres/component.hpp>

#include <core/application/exceptions.hpp>
#include <core/application/use_cases/commands/create_order/command.hpp>
#include <core/application/use_cases/commands/create_order/handler.hpp>
#include <infrastructure/adapters/postgres/order_repository.hpp>

#include "request.hpp"

namespace delivery::api::api_v1_orders {

namespace {

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

    auto command = core::application::use_cases::commands::create_order::
        CreateOrderCommand{std::move(request.basket_id),
                           std::move(request.address), request.weight};

    auto const create_order_handler = core::application::use_cases::commands::
        create_order::CreateOrderHandler{order_repository_};

    create_order_handler.Handle(std::move(command));

    return {};
  } catch (const core::application::ArgumentException& ex) {
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
