#include "controller.hpp"

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>

namespace delivery::api::adapters::http::api_v1_couriers {

namespace {

class Controller final : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  ~Controller() final = default;

  Controller(userver::components::ComponentConfig const& config,
             userver::components::ComponentContext const& context)
      : HttpHandlerJsonBase{config, context} {}

  static constexpr std::string_view kName = "handler-api-v1-couriers";

  [[nodiscard]] auto HandleRequestJsonThrow(
      userver::server::http::HttpRequest const&,
      userver::formats::json::Value const&,
      userver::server::request::RequestContext&) const
      -> userver::formats::json::Value final {
    return {};
  }
};

}  // namespace

auto AppendController(userver::components::ComponentList& components) -> void {
  components.Append<Controller>();
}

}  // namespace delivery::api::adapters::http::api_v1_couriers
