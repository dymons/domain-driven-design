#include "courier_repository.hpp"

#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>
#include <core/ports/exceptions.hpp>

namespace delivery::infrastructure::adapters::postgres {

namespace {

struct CourierRecord final {
  std::string id;
  std::string status;
  userver::formats::json::Value payload;
};

core::domain::courier::Courier FromRecord(CourierRecord&& record) {
  return core::domain::courier::Courier::Hydrate(
      core::domain::courier::CourierId{std::move(record.id)},
      core::domain::courier::CourierName{"CourierName"},
      core::domain::courier::Transport::kBicycle,
      core::domain::shared_kernel::Location::kMaxLocation,
      core::domain::courier::Status::Busy);
}

}  // namespace

class CourierRepository final : public core::ports::ICourierRepository {
  using core::ports::ICourierRepository::Courier;
  using core::ports::ICourierRepository::CourierId;

 public:
  ~CourierRepository() final = default;

  explicit CourierRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_(std::move(cluster)) {}

  auto Add(Courier const&) const -> void final {}

  auto Update(Courier const&) const -> void final {}

  auto GetById(CourierId const& courier_id) const -> Courier final try {
    auto result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "SELECT id, status, payload"
                          "FROM delivery.couriers"
                          "WHERE id = $1",
                          courier_id.GetUnderlying());

    return FromRecord(result.AsSingleRow<CourierRecord>(
        userver::storages::postgres::kRowTag));
  } catch (const userver::storages::postgres::NonSingleRowResultSet& ex) {
    userver::utils::LogErrorAndThrow<core::ports::CourierNotFound>(ex.what());
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
