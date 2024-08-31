#include "repository_mock_test.hpp"

#include <userver/utils/exception.hpp>

#include <core/domain/order/order.hpp>

namespace delivery::core::ports {

namespace {

class OrderRepository final : public IOrderRepository {
 public:
  ~OrderRepository() final = default;

  explicit OrderRepository(
      std::unordered_set<MutableSharedRef<domain::order::Order>> orders)
      : orders_{std::move(orders)} {}

  auto Add(SharedRef<core::domain::order::Order> const& order) const
      -> void final {
    auto raw_order = MakeMutableSharedRef<domain::order::Order>(*order);
    for (const auto& o : orders_) {
      if (o->GetId() == raw_order->GetId()) {
        userver::utils::LogErrorAndThrow<OrderAlreadyExists>("");
      }
    }

    orders_.insert(raw_order);
  }

  auto Update(SharedRef<core::domain::order::Order> const& order) const
      -> void final {
    auto raw_order = MakeMutableSharedRef<domain::order::Order>(*order);
    if (not orders_.contains(raw_order)) {
      userver::utils::LogErrorAndThrow<OrderNotFound>("");
    }

    orders_.erase(raw_order);
    Add(raw_order);
  }

  auto GetById(core::domain::order::OrderId const& order_id) const
      -> MutableSharedRef<core::domain::order::Order> final {
    for (const auto& order : orders_) {
      if (order->GetId() == order_id) {
        return order;
      }
    }

    userver::utils::LogErrorAndThrow<core::ports::OrderNotFound>("");
  }

  auto GetNotAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto result = std::vector<MutableSharedRef<core::domain::order::Order>>{};
    result.reserve(orders_.size());
    for (const auto& order : orders_) {
      if (not order->IsCourierAssigned()) {
        result.push_back(order);
      }
    }
    result.shrink_to_fit();
    return result;
  }

  auto GetAssigned() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    auto result = std::vector<MutableSharedRef<core::domain::order::Order>>{};
    result.reserve(orders_.size());
    for (const auto& order : orders_) {
      if (order->IsCourierAssigned()) {
        result.push_back(order);
      }
    }
    result.shrink_to_fit();
    return result;
  }

  auto GetOrders() const
      -> std::vector<MutableSharedRef<core::domain::order::Order>> final {
    return {orders_.begin(), orders_.end()};
  };

 private:
  mutable std::unordered_set<MutableSharedRef<domain::order::Order>> orders_;
};

}  // namespace

auto MockOrderRepository(
    std::unordered_set<MutableSharedRef<domain::order::Order>> orders)
    -> SharedRef<IOrderRepository> {
  return delivery::MakeSharedRef<OrderRepository>(std::move(orders));
}

}  // namespace delivery::core::ports
