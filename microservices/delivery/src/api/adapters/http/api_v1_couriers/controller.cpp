#include "controller.hpp"

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/storages/postgres/component.hpp>

#include <core/application/use_cases/queries/get_couriers/handler.hpp>
#include <core/application/use_cases/queries/get_couriers/query.hpp>
#include <core/application/use_cases/queries/get_couriers/response.hpp>
#include <infrastructure/adapters/postgres/courier_repository.hpp>

namespace delivery::api::adapters::http::api_v1_couriers {

namespace {

auto MakeResponse(
    core::application::use_cases::queries::get_couriers::Response200 const&
        response) -> userver::formats::json::Value {
  auto couriers_builder = userver::formats::json::ValueBuilder{
      userver::formats::common::Type::kArray};

  std::ranges::for_each(response.couriers, [&](auto const& courier) {
    auto courier_builder = userver::formats::json::ValueBuilder{};
    courier_builder["id"] = courier.GetId();
    courier_builder["name"] = courier.GetName();
    courier_builder["location"]["x"] = courier.GetLocation().GetX();
    courier_builder["location"]["y"] = courier.GetLocation().GetY();
    couriers_builder.PushBack(courier_builder.ExtractValue());
  });

  auto response_builder = userver::formats::json::ValueBuilder{};
  response_builder["couriers"] = couriers_builder.ExtractValue();
  return response_builder.ExtractValue();
}

class Controller final : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  ~Controller() final = default;

  Controller(userver::components::ComponentConfig const& config,
             userver::components::ComponentContext const& context)
      : HttpHandlerJsonBase{config, context},
        courier_repository_{
            infrastructure::adapters::postgres::MakeCourierRepository(
                context
                    .FindComponent<userver::components::Postgres>(
                        "delivery-database")
                    .GetCluster())} {}

  static constexpr std::string_view kName = "handler-api-v1-couriers";

  [[nodiscard]] auto HandleRequestJsonThrow(
      userver::server::http::HttpRequest const&,
      userver::formats::json::Value const&,
      userver::server::request::RequestContext&) const
      -> userver::formats::json::Value final {
    auto const get_couriers_handler = core::application::use_cases::queries::
        get_couriers::MakeGetCouriersHandler(courier_repository_);

    return std::visit(MakeResponse, get_couriers_handler->Handle({}));
  }

 private:
  SharedRef<core::ports::ICourierRepository> const courier_repository_;
};

}  // namespace

auto AppendController(userver::components::ComponentList& components) -> void {
  components.Append<Controller>();
}

}  // namespace delivery::api::adapters::http::api_v1_couriers
