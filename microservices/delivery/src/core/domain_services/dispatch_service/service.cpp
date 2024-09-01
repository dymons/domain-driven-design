#include "service.hpp"

#include <algorithm>
#include <set>

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>

#include "iservice.hpp"

namespace delivery::core::domain_services {

namespace {

struct Score final {
  domain::courier::Time time_to_delivery_location;
  MutableSharedRef<domain::courier::Courier> courier;

  auto operator<(Score const& that) const -> bool {
    return this->time_to_delivery_location < that.time_to_delivery_location;
  }

  static auto Estimate(MutableSharedRef<domain::courier::Courier>&& courier,
                       SharedRef<domain::order::Order> const& order) -> Score {
    return {
        .time_to_delivery_location =
            courier->CalculateTimeToPoint(order->GetDeliveryLocation()),
        .courier = std::move(courier),
    };
  }
};

class DispatchService final : public IDispatchService {
 public:
  ~DispatchService() final = default;

  [[nodiscard]] auto Dispatch(
      MutableSharedRef<domain::order::Order>&& order,
      std::vector<MutableSharedRef<domain::courier::Courier>>&& couriers) const
      -> DispatchResult final {
    auto scores = std::set<Score>{};
    std::ranges::transform(std::move(couriers),
                           std::inserter(scores, scores.begin()),
                           [&](auto courier) {
                             return Score::Estimate(std::move(courier), order);
                           });

    if (not scores.empty()) {
      auto best_courier = scores.begin()->courier;
      order->AssignCourier(best_courier->GetId());
      best_courier->StartWork();

      return {.order = std::move(order), .courier = std::move(best_courier)};
    }

    return {.order = std::move(order), .courier = std::nullopt};
  }
};

}  // namespace

auto MakeDispatchService() -> SharedRef<IDispatchService> {
  return delivery::MakeSharedRef<DispatchService>();
}

}  // namespace delivery::core::domain_services
