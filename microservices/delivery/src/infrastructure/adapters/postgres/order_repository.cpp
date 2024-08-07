#include "order_repository.hpp"

#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/exception.hpp>

#include <core/domain/order/order.hpp>
#include <core/ports/order_repository/irepository.hpp>

#include "db/sql.hpp"
#include "dto/order.hpp"

namespace delivery::infrastructure::adapters::postgres {

namespace {

class OrderRepository final : public core::ports::IOrderRepository {
 public:
  ~OrderRepository() final = default;

  explicit OrderRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_(std::move(cluster)) {}

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
        "UPDATE delivery.orders"
        "SET id=$1, status=$2, courier_id=$3, delivery_location=$4, weight=$5"
        "WHERE id = $1",
        record.id, record.status, record.courier_id, record.delivery_location,
        record.weight);

    if (result.IsEmpty()) {
      userver::utils::LogErrorAndThrow<core::ports::OrderNotFound>(
          fmt::format("Not found order by id={}", order->GetId()));
    }
  }

  auto GetById(core::domain::order::OrderId const& order_id) const
      -> MutableSharedRef<core::domain::order::Order> final try {
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "SELECT id, status, courier_id, delivery_location, weight"
        "FROM delivery.orders"
        "WHERE id = $1",
        order_id.GetUnderlying());

    return dto::Convert(
        result.AsSingleRow<dto::Order>(userver::storages::postgres::kRowTag));
  } catch (const userver::storages::postgres::NonSingleRowResultSet& ex) {
    userver::utils::LogErrorAndThrow<core::ports::OrderNotFound>(ex.what());
  }

  auto GetNotAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "SELECT id, status, courier_id, delivery_location, weight"
        "FROM delivery.orders"
        "WHERE status != $1",
        core::domain::order::OrderStatus::kAssigned.ToString());

    auto const records = result.AsContainer<std::vector<dto::Order>>();
    auto orders = std::vector<MutableSharedRef<core::domain::order::Order>>{};
    orders.reserve(records.size());
    std::ranges::transform(
        records, std::back_inserter(orders),
        [](auto const& record) { return dto::Convert(record); });

    return orders;
  }

  auto GetAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "SELECT id, status, courier_id, delivery_location, weight"
        "FROM delivery.orders"
        "WHERE status = $1",
        core::domain::order::OrderStatus::kAssigned.ToString());

    auto const records = result.AsContainer<std::vector<dto::Order>>();
    auto orders = std::vector<MutableSharedRef<core::domain::order::Order>>{};
    orders.reserve(records.size());
    std::ranges::transform(
        records, std::back_inserter(orders),
        [](auto const& record) { return dto::Convert(record); });

    return orders;
  }

  auto GetOrders() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto const result = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "SELECT id, status, courier_id, delivery_location, weight "
        "FROM delivery.orders");

    auto const records = result.AsContainer<std::vector<dto::Order>>(
        userver::storages::postgres::RowTag{});
    auto orders = std::vector<MutableSharedRef<core::domain::order::Order>>{};
    orders.reserve(records.size());
    std::ranges::transform(
        records, std::back_inserter(orders),
        [](auto const& record) { return dto::Convert(record); });

    return orders;
  };

 private:
  userver::storages::postgres::ClusterPtr const cluster_;
};

}  // namespace

auto MakeOrderRepository(userver::storages::postgres::ClusterPtr cluster)
    -> SharedRef<core::ports::IOrderRepository> {
  return userver::utils::MakeSharedRef<const OrderRepository>(
      std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
