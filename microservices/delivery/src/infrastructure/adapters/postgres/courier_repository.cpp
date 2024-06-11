#include "courier_repository.hpp"

#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>

#include "dto/courier.hpp"

namespace delivery::infrastructure::adapters::postgres {

namespace {

class CourierRepository final : public core::ports::ICourierRepository {
 public:
  ~CourierRepository() final = default;

  explicit CourierRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_(std::move(cluster)) {}

  auto Add(core::domain::courier::Courier const& courier) const -> void final {
    auto const record = dto::Convert(courier);
    auto const result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "INSERT INTO delivery.couriers"
                          "(id, name, transport, current_location, status)"
                          "VALUES ($1, $2, $3, $4, $5)",
                          record.id, record.name, record.transport,
                          record.current_location, record.status);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::CourierAlreadyExists>(
          fmt::format("Courier with id={} already exists", courier.GetId()));
    }
  }

  auto Update(core::domain::courier::Courier const& courier) const
      -> void final {
    auto const record = dto::Convert(courier);
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "UPDATE delivery.couriers"
        "SET id=$1, name=$2, transport=$3, current_location=$4, status=$5"
        "WHERE id = $1",
        record.id, record.name, record.transport, record.current_location,
        record.status);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::CourierNotFound>(
          fmt::format("Not found courier by id={}", courier.GetId()));
    }
  }

  auto GetById(core::domain::courier::CourierId const& courier_id) const
      -> core::domain::courier::Courier final try {
    auto const result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "SELECT id, name, transport, current_location, status"
                          "FROM delivery.couriers"
                          "WHERE id = $1",
                          courier_id.GetUnderlying());

    return dto::Convert(
        result.AsSingleRow<dto::Courier>(userver::storages::postgres::kRowTag));
  } catch (const userver::storages::postgres::NonSingleRowResultSet& ex) {
    userver::utils::LogErrorAndThrow<core::ports::CourierNotFound>(ex.what());
  }

  auto GetByReadyStatus() const
      -> std::vector<core::domain::courier::Courier> final {
    return GetByStatus(core::domain::courier::CourierStatus::kReady);
  }

  auto GetByBusyStatus() const
      -> std::vector<core::domain::courier::Courier> final {
    return GetByStatus(core::domain::courier::CourierStatus::kBusy);
  }

 private:
  auto GetByStatus(core::domain::courier::CourierStatus status) const
      -> std::vector<core::domain::courier::Courier> {
    auto const result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "SELECT id, name, transport, current_location, status"
                          "FROM delivery.couriers"
                          "WHERE status = $1",
                          status.ToString());

    auto const records = result.AsContainer<std::vector<dto::Courier>>();
    auto couriers = std::vector<core::domain::courier::Courier>{};
    couriers.reserve(records.size());
    for (auto const& record : records) {
      couriers.push_back(dto::Convert(record));
    }

    return couriers;
  }

  const userver::storages::postgres::ClusterPtr cluster_;
};

}  // namespace

auto MakeCourierRepository(userver::storages::postgres::ClusterPtr cluster)
    -> userver::utils::SharedRef<const core::ports::ICourierRepository> {
  return userver::utils::MakeSharedRef<const CourierRepository>(
      std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
