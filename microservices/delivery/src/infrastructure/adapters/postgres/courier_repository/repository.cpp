#include "repository.hpp"

#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>
#include <core/ports/courier_repository/irepository.hpp>
#include <infrastructure/adapters/postgres/query_execution/query_execution.hpp>
#include <utils/ranges.hpp>

#include "db/sql.hpp"
#include "dto/courier.hpp"

namespace delivery::infrastructure::adapters::postgres {

namespace {

auto FromRecords(std::vector<dto::Courier>&& records) {
  return std::move(records) | std::views::transform([](auto&& record) {
           return dto::Convert(std::move(record));
         }) |
         ranges::to<std::vector>();
}

class CourierRepository final : public core::ports::ICourierRepository {
 public:
  ~CourierRepository() final = default;

  explicit CourierRepository(QueryExecution query_execution)
      : query_execution_{std::move(query_execution)} {}

  auto Add(SharedRef<core::domain::courier::Courier> const& courier) const
      -> void final {
    auto const record = dto::Convert(courier);
    auto const result = query_execution_.Execute(
        userver::storages::postgres::ClusterHostType::kMaster, sql::kAddCourier,
        record.id, record.name, record.transport, record.current_location,
        record.status);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::CourierAlreadyExists>(
          fmt::format("Courier with id={} already exists", courier->GetId()));
    }
  }

  auto Update(SharedRef<core::domain::courier::Courier> const& courier) const
      -> void final {
    auto const record = dto::Convert(courier);
    auto const result = query_execution_.Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::kUpdateCourier, record.id, record.name, record.transport,
        record.current_location, record.status);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::CourierNotFound>(
          fmt::format("Not found courier by id={}", courier->GetId()));
    }
  }

  [[nodiscard]] auto GetById(core::domain::CourierId const& courier_id) const
      -> MutableSharedRef<core::domain::courier::Courier> final try {
    auto const result = query_execution_.Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::kGetCourierById, courier_id.GetUnderlying());

    return dto::Convert(
        result.AsSingleRow<dto::Courier>(userver::storages::postgres::kRowTag));
  } catch (const userver::storages::postgres::NonSingleRowResultSet& ex) {
    userver::utils::LogErrorAndThrow<core::ports::CourierNotFound>(ex.what());
  }

  [[nodiscard]] auto GetByReadyStatus() const
      -> std::vector<MutableSharedRef<core::domain::courier::Courier>> final {
    return GetByStatus(core::domain::courier::CourierStatus::kReady);
  }

  [[nodiscard]] auto GetByBusyStatus() const
      -> std::vector<MutableSharedRef<core::domain::courier::Courier>> final {
    return GetByStatus(core::domain::courier::CourierStatus::kBusy);
  }

  [[nodiscard]] auto GetCouriers() const
      -> std::vector<MutableSharedRef<core::domain::courier::Courier>> final {
    auto const result = query_execution_.Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::kGetCouriers);

    auto records = result.AsContainer<std::vector<dto::Courier>>(
        userver::storages::postgres::RowTag{});
    return FromRecords(std::move(records));
  }

 private:
  [[nodiscard]] auto GetByStatus(
      core::domain::courier::CourierStatus const status) const
      -> std::vector<MutableSharedRef<core::domain::courier::Courier>> {
    auto const result = query_execution_.Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::kGetCouriersByStatus, status.ToString());

    auto records = result.AsContainer<std::vector<dto::Courier>>();
    return FromRecords(std::move(records));
  }

  QueryExecution const query_execution_;
};

}  // namespace

auto MakeCourierRepository(userver::storages::postgres::ClusterPtr cluster)
    -> SharedRef<core::ports::ICourierRepository> {
  return delivery::MakeSharedRef<CourierRepository>(
      QueryExecution{std::move(cluster)});
}

auto MakeCourierRepository(
    MutableSharedRef<userver::storages::postgres::Transaction> transaction)
    -> SharedRef<core::ports::ICourierRepository> {
  return delivery::MakeSharedRef<CourierRepository>(
      QueryExecution{std::move(transaction)});
}

}  // namespace delivery::infrastructure::adapters::postgres
