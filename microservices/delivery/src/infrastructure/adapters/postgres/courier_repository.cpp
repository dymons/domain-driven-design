#include "courier_repository.hpp"

#include <ranges>

#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/algo.hpp>
#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>
#include <core/ports/exceptions.hpp>

#include "dto/courier.hpp"
#include "dto/location.hpp"
#include "dto/transport.hpp"

namespace delivery::infrastructure::adapters::postgres {

// TODO (dymons) Use enum at PG to store status

namespace {

core::domain::courier::Courier FromRecord(dto::Courier const& record) {
  return core::domain::courier::Courier::Hydrate(
      core::domain::courier::CourierId{record.id},
      core::domain::courier::CourierName{record.name},
      dto::Convert(record.transport), dto::Convert(record.current_location),
      core::domain::courier::FromString(record.status));
}

dto::Courier ToRecord(core::domain::courier::Courier const& courier) {
  return {.id = courier.GetId().GetUnderlying(),
          .name = courier.GetName().GetUnderlying(),
          .status = ToString(courier.GetStatus()),
          .transport = dto::Convert(courier.GetTransport()),
          .current_location = dto::Convert(courier.GetCurrentLocation())};
}

}  // namespace

class CourierRepository final : public core::ports::ICourierRepository {
  using core::ports::ICourierRepository::Courier;
  using core::ports::ICourierRepository::CourierId;

 public:
  ~CourierRepository() final = default;

  explicit CourierRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_(std::move(cluster)) {}

  auto Add(Courier const& courier) const -> void final {
    auto const record = ToRecord(courier);
    auto const result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "INSERT INTO delivery.couriers "
                          "(id, name, transport, current_location, status)"
                          "VALUES ($1, $2, $3, $4, $5)",
                          record.id, record.name, record.transport,
                          record.current_location, record.status);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::CourierAlreadyExists>(
          fmt::format("Courier with id={} already exists", courier.GetId()));
    }
  }

  auto Update(Courier const& courier) const -> void final {
    auto const record = ToRecord(courier);
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "UPDATE delivery.couriers "
        "SET id=$1, name=$2, transport=$3, current_location=$4, status=$5"
        "WHERE id = $1",
        record.id, record.name, record.transport, record.current_location,
        record.status);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::CourierNotFound>(
          fmt::format("Not found courier by id={}", courier.GetId()));
    }
  }

  auto GetById(CourierId const& courier_id) const -> Courier final try {
    auto result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "SELECT id, name, transport, current_location, status"
                          "FROM delivery.couriers"
                          "WHERE id = $1",
                          courier_id.GetUnderlying());

    return FromRecord(
        result.AsSingleRow<dto::Courier>(userver::storages::postgres::kRowTag));
  } catch (const userver::storages::postgres::NonSingleRowResultSet& ex) {
    userver::utils::LogErrorAndThrow<core::ports::CourierNotFound>(ex.what());
  }

  auto GetByReadyStatus() const -> std::vector<Courier> final {
    return GetByStatus(core::domain::courier::Status::Ready);
  }

  auto GetByBusyStatus() const -> std::vector<Courier> final {
    return GetByStatus(core::domain::courier::Status::Busy);
  }

 private:
  auto GetByStatus(core::domain::courier::Status status) const
      -> std::vector<Courier> {
    auto result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "SELECT id, name, transport, current_location, status"
                          "FROM delivery.couriers"
                          "WHERE status = $1",
                          ToString(status));

    auto records = result.AsContainer<std::vector<dto::Courier>>();
    auto couriers = records | std::ranges::views::transform(FromRecord);
    return userver::utils::AsContainer<std::vector<Courier>>(couriers);
  }

  const userver::storages::postgres::ClusterPtr cluster_;
};

auto MakeCourierRepository(userver::storages::postgres::ClusterPtr cluster)
    -> userver::utils::SharedRef<const core::ports::ICourierRepository> {
  return userver::utils::MakeSharedRef<const CourierRepository>(
      std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
