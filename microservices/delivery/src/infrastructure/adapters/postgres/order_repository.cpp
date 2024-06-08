#include "order_repository.hpp"

#include <userver/storages/postgres/cluster.hpp>

#include <core/domain/order/order.hpp>

namespace delivery::infrastructure::adapters::postgres {

class OrderRepository final : public core::ports::IOrderRepository {
  using core::ports::IOrderRepository::Order;
  using core::ports::IOrderRepository::OrderId;

 public:
  ~OrderRepository() final = default;

  explicit OrderRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_(std::move(cluster)) {}

  auto Add(Order const&) const -> void final {}

  auto Update(Order const&) const -> void final {}

  auto GetById(OrderId const&) const -> Order final {
    return Order::Create(core::domain::order::BasketId{"BasketId"},
                         core::domain::shared_kernel::Location::kMaxLocation,
                         core::domain::shared_kernel::Weight{0});
  }

  auto GetAllNotAssigned() const -> std::vector<Order> final { return {}; }

  auto GetAllAssigned() const -> std::vector<Order> final { return {}; }

 private:
  userver::storages::postgres::ClusterPtr cluster_;
};

auto MakeOrderRepository(userver::storages::postgres::ClusterPtr cluster)
    -> userver::utils::SharedRef<const core::ports::IOrderRepository> {
  return userver::utils::MakeSharedRef<const OrderRepository>(
      std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
