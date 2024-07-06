#include "controller.hpp"

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/storages/postgres/component.hpp>

#include <core/application/use_cases/queries/get_active_orders/handler.hpp>
#include <core/application/use_cases/queries/get_active_orders/query.hpp>
#include <core/application/use_cases/queries/get_active_orders/response.hpp>
#include <infrastructure/adapters/postgres/order_repository.hpp>

namespace delivery::api::adapters::http::api_v1_orders_active {

namespace {

auto MakeResponse(
    core::application::use_cases::queries::get_active_orders::Response200 const&
        response) -> userver::formats::json::Value {
  auto response_builder = userver::formats::json::ValueBuilder{
      userver::formats::common::Type::kArray};

  std::ranges::for_each(response.orders, [&](auto const& order) {
    auto order_builder = userver::formats::json::ValueBuilder{};
    order_builder["id"] = order.GetId();
    order_builder["location"]["x"] = order.GetLocation().GetX();
    order_builder["location"]["y"] = order.GetLocation().GetY();
    response_builder.PushBack(order_builder.ExtractValue());
  });

  return response_builder.ExtractValue();
}

class Controller final : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  ~Controller() final = default;

  Controller(userver::components::ComponentConfig const& config,
             userver::components::ComponentContext const& context)
      : HttpHandlerJsonBase{config, context},
        order_repository_{
            infrastructure::adapters::postgres::MakeOrderRepository(
                context
                    .FindComponent<userver::components::Postgres>(
                        "delivery-database")
                    .GetCluster())} {}

  static constexpr std::string_view kName = "handler-api-v1-orders-active";

  [[nodiscard]] auto HandleRequestJsonThrow(
      userver::server::http::HttpRequest const&,
      userver::formats::json::Value const&,
      userver::server::request::RequestContext&) const
      -> userver::formats::json::Value final {
    auto const get_active_orders_handler =
        core::application::use_cases::queries::get_active_orders::
            MakeGetActiveOrdersHandler(order_repository_);

    return std::visit(MakeResponse, get_active_orders_handler->Handle({}));
  }

 private:
  SharedRef<core::ports::IOrderRepository> const order_repository_;
};

}  // namespace

auto AppendController(userver::components::ComponentList& components) -> void {
  components.Append<Controller>();
}

}  // namespace delivery::api::adapters::http::api_v1_orders_active
