#include "repository_mock.hpp"

#include <algorithm>
#include <ranges>

#include <userver/utils/exception.hpp>

#include <core/domain/order/order.hpp>

#include "irepository.hpp"

namespace delivery::core::ports {

namespace {

class OrderRepository final : public IOrderRepository {
 public:
  ~OrderRepository() final = default;

  explicit OrderRepository(
      std::vector<MutableSharedRef<domain::order::Order>> orders)
      : orders_{std::move(orders)} {}

  auto Add(SharedRef<core::domain::order::Order> const& new_order) const
      -> void final {
    auto const is_order_already_exists = std::ranges::any_of(
        orders_, [&](const auto& order) { return *order == *new_order; });

    if (is_order_already_exists) {
      userver::utils::LogErrorAndThrow<OrderAlreadyExists>("");
    }

    orders_.push_back(MakeMutableSharedRef<domain::order::Order>(*new_order));
  }

  auto Update(SharedRef<core::domain::order::Order> const& new_order) const
      -> void final {
    auto const it = std::ranges::find_if(orders_, [&](const auto& order) {
      return order->GetId() == new_order->GetId();
    });

    if (it == orders_.end()) {
      userver::utils::LogErrorAndThrow<OrderAlreadyExists>("");
    }

    *it = MakeMutableSharedRef<domain::order::Order>(*new_order);
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
  mutable std::vector<MutableSharedRef<domain::order::Order>> orders_;
};

}  // namespace

auto MockOrderRepository(
    std::vector<MutableSharedRef<domain::order::Order>> orders)
    -> SharedRef<IOrderRepository> {
  return delivery::MakeSharedRef<OrderRepository>(std::move(orders));
}

}  // namespace delivery::core::ports
