#include "order_repository.hpp"

#include <userver/storages/postgres/cluster.hpp>

#include <core/domain/order/order.hpp>

namespace delivery::infrastructure::adapters::postgres {

class OrderRepository final : public core::ports::IOrderRepository {
 public:
  ~OrderRepository() final = default;

  explicit OrderRepository(userver::storages::postgres::ClusterPtr cluster)
      : cluster_(std::move(cluster)) {}

  auto Add(core::domain::order::Order const&) const -> void final {}

  auto Update(core::domain::order::Order const&) const -> void final {}

  auto GetById(core::domain::order::OrderId const&) const
      -> core::domain::order::Order final {
    return core::domain::order::Order::Create(
        core::domain::order::BasketId{"BasketId"},
        core::domain::shared_kernel::Location::kMaxLocation,
        core::domain::shared_kernel::Weight{0});
  }

  auto GetAllNotAssigned() const
      -> std::vector<core::domain::order::Order> final {
    return {};
  }

  auto GetAllAssigned() const -> std::vector<core::domain::order::Order> final {
    return {};
  }

 private:
  userver::storages::postgres::ClusterPtr cluster_;
};

userver::utils::SharedRef<const core::ports::IOrderRepository>
MakeCourierRepository(userver::storages::postgres::ClusterPtr cluster) {
  return userver::utils::MakeSharedRef<const OrderRepository>(
      std::move(cluster));
}

}  // namespace delivery::infrastructure::adapters::postgres
