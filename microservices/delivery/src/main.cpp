#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include <api/adapters/http/api_v1_orders/controller.hpp>

auto main(int argc, char* argv[]) -> int {
  auto components =
      userver::components::MinimalServerComponentList()
          .Append<userver::server::handlers::Ping>()
          .Append<userver::components::TestsuiteSupport>()
          .Append<userver::components::HttpClient>()
          .Append<userver::clients::dns::Component>()
          .Append<userver::server::handlers::TestsControl>()
          .Append<userver::components::Postgres>("delivery-database");

  delivery::api::adapters::http::api_v1_orders::AppendController(components);

  return userver::utils::DaemonMain(argc, argv, components);
}
