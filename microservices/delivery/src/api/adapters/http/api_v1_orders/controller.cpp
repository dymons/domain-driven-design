#include "controller.hpp"

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

#include <core/application/use_cases/commands/create_order/command.hpp>
#include <core/application/use_cases/commands/create_order/handler.hpp>
#include <infrastructure/adapters/postgres/order_repository.hpp>

namespace delivery::api::api_v1_orders {

namespace {

class Controller final : public userver::server::handlers::HttpHandlerBase {
 public:
  ~Controller() final = default;

  Controller(const userver::components::ComponentConfig& config,
             const userver::components::ComponentContext& context)
      : HttpHandlerBase(config, context),
        pg_cluster_{context
                        .FindComponent<userver::components::Postgres>(
                            "delivery-database")
                        .GetCluster()} {}

  static constexpr std::string_view kName = "handler-api-v1-orders";

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const final {
    auto command =
        application::use_cases::commands::create_order::CreateOrderCommand{
            request.GetArg("basket_id"), request.GetArg("address"),
            std::stoi(request.GetArg("weight"))};

    auto const create_order_handler =
        application::use_cases::commands::create_order::CreateOrderHandler{
            infrastructure::adapters::postgres::MakeOrderRepository(
                pg_cluster_)};

    create_order_handler.Handle(std::move(command));

    return {};
  }

 private:
  userver::storages::postgres::ClusterPtr pg_cluster_;
};

}  // namespace

void AppendController(userver::components::ComponentList& component_list) {
  component_list.Append<Controller>();
}

}  // namespace delivery::api::api_v1_orders
