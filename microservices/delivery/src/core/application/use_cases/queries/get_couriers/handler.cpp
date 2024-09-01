#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/ports/courier_repository/irepository.hpp>

#include "ihandler.hpp"
#include "query.hpp"
#include "response.hpp"

namespace delivery::core::application::use_cases::queries::get_couriers {

namespace {

Courier ConvertCourier(SharedRef<domain::courier::Courier> const& courier) {
  return {courier->GetId().GetUnderlying(), courier->GetName().GetUnderlying(),
          Location{courier->GetCurrentLocation().GetX().GetUnderlying(),
                   courier->GetCurrentLocation().GetY().GetUnderlying()}};
}

class GetCouriersHandler final : public IGetCouriersHandler {
 public:
  ~GetCouriersHandler() final = default;

  explicit GetCouriersHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository)
      : courier_repository_(std::move(courier_repository)) {}

  [[nodiscard]] auto Handle(GetCouriersQuery&&) const
      -> std::vector<Courier> final {
    auto couriers = courier_repository_->GetCouriers();

    // TODO (dymons) Wait support std::ranges::to at C++23 (libstdc++14)
    // return couriers | std::ranges::transform(ConvertCourier)
    //                 | std::ranges::to<std::vector>();

    auto result = std::vector<Courier>{};
    result.reserve(couriers.size());
    for (auto const& courier : couriers) {
      result.emplace_back(ConvertCourier(courier));
    }

    return result;
  }

 private:
  SharedRef<core::ports::ICourierRepository> const courier_repository_;
};

}  // namespace

auto MakeGetCouriersHandler(
    SharedRef<core::ports::ICourierRepository> courier_repository)
    -> SharedRef<IGetCouriersHandler> {
  return delivery::MakeSharedRef<GetCouriersHandler>(
      std::move(courier_repository));
}

}  // namespace delivery::core::application::use_cases::queries::get_couriers
