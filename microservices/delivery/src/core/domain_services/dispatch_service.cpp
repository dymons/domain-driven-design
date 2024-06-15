#include "dispatch_service.hpp"

#include <algorithm>
#include <set>

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>
#include "idispatch_service.hpp"

namespace delivery::core::domain_services {

namespace {

struct Score {
  domain::courier::Courier courier;
  domain::courier::Time time_to_delivery_location;

  auto operator<(Score const& that) const -> bool {
    return this->time_to_delivery_location < that.time_to_delivery_location;
  }

  static auto Estimate(domain::courier::Courier const& courier,
                       domain::order::Order const& order) -> Score {
    return {.courier = courier,
            .time_to_delivery_location =
                courier.CalculateTimeToPoint(order.GetDeliveryLocation())};
  }
};

class DispatchService final : public IDispatchService {
 public:
  ~DispatchService() final = default;

  [[nodiscard]] auto Dispatch(domain::order::Order&& order,
                              std::unordered_set<domain::courier::Courier>&&
                                  couriers) const -> DispatchResult final {
    auto scores = std::set<Score>{};
    std::ranges::transform(
        couriers, std::inserter(scores, scores.begin()),
        [&](auto&& courier) { return Score::Estimate(courier, order); });

    if (not scores.empty()) {
      auto best_courier = scores.begin()->courier;
      auto const courier_id = best_courier.GetId().GetUnderlying();

      order.AssignCourier(domain::order::CourierId{courier_id});
      best_courier.StartWork();

      return {
          .order = userver::utils::MakeSharedRef<domain::order::Order>(
              std::move(order)),
          .courier = userver::utils::MakeSharedRef<domain::courier::Courier>(
              std::move(best_courier)),
      };
    }

    return {
        .order = userver::utils::MakeSharedRef<domain::order::Order>(
            std::move(order)),
        .courier = std::nullopt,
    };
  }
};

}  // namespace

auto MakeDispatchService() -> SharedRef<IDispatchService> {
  return userver::utils::MakeSharedRef<const DispatchService>();
}

}  // namespace delivery::core::domain_services
