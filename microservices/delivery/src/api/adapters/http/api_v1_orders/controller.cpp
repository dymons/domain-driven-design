#include "controller.hpp"

#include <userver/server/handlers/http_handler_base.hpp>

namespace delivery::api::api_v1_orders {

namespace {

class Controller final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "/api/v1/orders";

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest&,
      userver::server::request::RequestContext&) const final {
    return {};
  }
};

}  // namespace

void AppendController(userver::components::ComponentList& component_list) {
  component_list.Append<Controller>();
}

}  // namespace delivery::api::api_v1_orders
