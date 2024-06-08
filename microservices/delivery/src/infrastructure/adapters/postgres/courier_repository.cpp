#include "courier_repository.hpp"

#include <ranges>

#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/algo.hpp>
#include <userver/utils/exception.hpp>

#include <core/domain/courier/courier.hpp>
#include <core/ports/exceptions.hpp>

namespace delivery::infrastructure::adapters::postgres {

namespace {

struct TransportRecord {
  int id;
  std::string name;
  int speed;
  int capacity;
};

struct LocationRecord {
  int x;
  int y;
};

struct CourierRecord final {
  std::string id;
  std::string name;
  TransportRecord transport;
  LocationRecord current_location;
  std::string status;
};

core::domain::courier::Courier FromRecord(CourierRecord const& record) {
  return core::domain::courier::Courier::Hydrate(
      core::domain::courier::CourierId{record.id},
      core::domain::courier::CourierName{record.name},
      core::domain::courier::Transport::kBicycle,
      core::domain::shared_kernel::Location::kMaxLocation,
      core::domain::courier::Status::Busy);
}

CourierRecord ToRecord(core::domain::courier::Courier const& courier) {
  return {
      .id = courier.GetId().GetUnderlying(),
      .name = courier.GetName().GetUnderlying(),
      .transport =
          TransportRecord{
              .id = courier.GetTransport().GetId().GetUnderlying(),
              .name = courier.GetTransport().GetName().GetUnderlying(),
              .speed = courier.GetTransport().GetSpeed().GetUnderlying(),
              .capacity = courier.GetTransport().GetCapacity().GetWeight(),
          },
      .current_location =
          {
              .x = courier.GetCurrentLocation().GetX().GetUnderlying(),
              .y = courier.GetCurrentLocation().GetY().GetUnderlying(),
          },
      .status = ToString(courier.GetStatus()),
  };
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

    return FromRecord(result.AsSingleRow<CourierRecord>(
        userver::storages::postgres::kRowTag));
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

    auto records = result.AsContainer<std::vector<CourierRecord>>();
    auto couriers = records | std::ranges::views::transform(FromRecord);
    return userver::utils::AsContainer<std::vector<Courier>>(couriers);
  }

  userver::storages::postgres::ClusterPtr cluster_;
};

userver::utils::SharedRef<const core::ports::ICourierRepository>
MakeCourierRepository(userver::storages::postgres::ClusterPtr cluster) {
  return userver::utils::MakeSharedRef<const CourierRepository>(
      std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    delivery::infrastructure::adapters::postgres::TransportRecord> {
  static constexpr DBTypeName postgres_name = "transport";
};

template <>
struct ::userver::storages::postgres::io::CppToUserPg<
    delivery::infrastructure::adapters::postgres::LocationRecord> {
  static constexpr DBTypeName postgres_name = "location";
};
