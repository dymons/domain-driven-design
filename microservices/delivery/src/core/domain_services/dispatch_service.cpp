#include "dispatch_service.hpp"

#include <algorithm>
#include <set>

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>
#include "idispatch_service.hpp"

namespace delivery::core::domain_services {

namespace {

struct Score {
  domain::courier::CourierId courier_id{};
  domain::courier::Time time_to_delivery_location{};

  auto operator<(Score const& that) const -> bool {
    return this->time_to_delivery_location < that.time_to_delivery_location;
  }

  static auto Estimate(domain::courier::Courier const& courier,
                       domain::order::Order const& order) -> Score {
    return {.courier_id = courier.GetId(),
            .time_to_delivery_location =
                courier.CalculateTimeToPoint(order.GetDeliveryLocation())};
  }
};

class DispatchService final : public IDispatchService {
 public:
  ~DispatchService() final = default;

  auto Dispatch(domain::order::Order&& order,
                std::vector<domain::courier::Courier> const& couriers) const
      -> domain::order::Order final {
    auto scores = std::set<Score>{};
    std::ranges::transform(
        couriers, std::inserter(scores, scores.begin()),
        [&](auto const& courier) { return Score::Estimate(courier, order); });

    if (not scores.empty()) {
      auto const courier_id = scores.begin()->courier_id;
      order.AssignCourier(domain::order::CourierId{courier_id.GetUnderlying()});
    }

    return order;
  }
};

}  // namespace

auto MakeDispatchService() -> SharedRef<IDispatchService> {
  return userver::utils::MakeSharedRef<const DispatchService>();
}

}  // namespace delivery::core::domain_services
