#include "repository.hpp"

#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/exception.hpp>

#include <core/domain/order/order.hpp>
#include <core/ports/order_repository/irepository.hpp>
#include <utils/ranges.hpp>

#include "db/sql.hpp"
#include "dto/order.hpp"

namespace delivery::infrastructure::adapters::postgres {

namespace {

auto FromRecords(std::vector<dto::Order>&& records) {
  return std::move(records) | std::views::transform([](auto&& record) {
           return dto::Convert(std::move(record));
         }) |
         ranges::to<std::vector>();
}

class OrderRepository final : public core::ports::IOrderRepository {
 public:
  ~OrderRepository() final = default;

  explicit OrderRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_{std::move(cluster)} {}

  auto Add(SharedRef<core::domain::order::Order> const& order) const
      -> void final {
    auto const record = dto::Convert(order);
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster, sql::kAddOrder,
        record.id, record.status, record.courier_id, record.delivery_location.x,
        record.delivery_location.y, record.weight.value);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::OrderAlreadyExists>(
          fmt::format("Order with id={} already exists", order->GetId()));
    }
  }

  auto Update(SharedRef<core::domain::order::Order> const& order) const
      -> void final {
    auto const record = dto::Convert(order);
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::kUpdateOrder, record.id, record.status, record.courier_id,
        record.delivery_location, record.weight);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::OrderNotFound>(
          fmt::format("Not found order by id={}", order->GetId()));
    }
  }

  [[nodiscard]] auto GetById(core::domain::order::OrderId const& order_id) const
      -> MutableSharedRef<core::domain::order::Order> final try {
    auto const result =
        cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          sql::kGetOrderById, order_id.GetUnderlying());

    return dto::Convert(
        result.AsSingleRow<dto::Order>(userver::storages::postgres::kRowTag));
  } catch (const userver::storages::postgres::NonSingleRowResultSet& ex) {
    userver::utils::LogErrorAndThrow<core::ports::OrderNotFound>(ex.what());
  }

  [[nodiscard]] auto GetNotAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::kGetOrdersExcludeByStatus,
        core::domain::order::OrderStatus::kAssigned.ToString());

    return FromRecords(result.AsContainer<std::vector<dto::Order>>());
  }

  [[nodiscard]] auto GetAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::kGetOrdersByStatus,
        core::domain::order::OrderStatus::kAssigned.ToString());

    return FromRecords(result.AsContainer<std::vector<dto::Order>>());
  }

  [[nodiscard]] auto GetOrders() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster, sql::kGetOrders);

    auto records = result.AsContainer<std::vector<dto::Order>>(
        userver::storages::postgres::RowTag{});
    return FromRecords(std::move(records));
  };

 private:
  userver::storages::postgres::ClusterPtr const cluster_;
};

}  // namespace

auto MakeOrderRepository(userver::storages::postgres::ClusterPtr cluster)
    -> SharedRef<core::ports::IOrderRepository> {
  return MakeSharedRef<OrderRepository>(std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
