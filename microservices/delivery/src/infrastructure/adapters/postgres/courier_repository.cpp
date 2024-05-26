#include "courier_repository.hpp"

#include <userver/storages/postgres/cluster.hpp>

#include <core/domain/courier/courier.hpp>

namespace delivery::infrastructure::adapters::postgres {

class CourierRepository final : public core::ports::ICourierRepository {
  using core::ports::ICourierRepository::Courier;
  using core::ports::ICourierRepository::CourierId;

 public:
  ~CourierRepository() final = default;

  explicit CourierRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_(std::move(cluster)) {}

  auto Add(Courier const&) const -> void final {}

  auto Update(Courier const&) const -> void final {}

  auto GetById(CourierId const&) const -> Courier final {
    return Courier::Create(core::domain::courier::CourierName{"CourierName"},
                           core::domain::courier::Transport::kBicycle);
  }

  auto GetAllReady() const -> std::vector<Courier> final { return {}; }

  auto GetAllBusy() const -> std::vector<Courier> final { return {}; }

 private:
  userver::storages::postgres::ClusterPtr cluster_;
};

userver::utils::SharedRef<const core::ports::ICourierRepository>
MakeCourierRepository(userver::storages::postgres::ClusterPtr cluster) {
  return userver::utils::MakeSharedRef<const CourierRepository>(
      std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
