#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/ports/icourier_repository.hpp>

namespace delivery::core::application::use_cases::queries::get_couriers {

namespace {

class GetCouriersHandler final : public IGetCouriersHandler {
 public:
  ~GetCouriersHandler() final = default;

  explicit GetCouriersHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository)
      : courier_repository_(std::move(courier_repository)) {}

  auto Handle(GetCouriersQuery&&) const -> Response final {
    auto couriers = courier_repository_->GetCouriers();

    auto response = Response200{};
    response.couriers.reserve(couriers.size());
    for (auto&& courier : couriers) {
      response.couriers.emplace_back(
          courier->GetId().GetUnderlying(), courier->GetName().GetUnderlying(),
          Location{
              .x = courier->GetCurrentLocation().GetX().GetUnderlying(),
              .y = courier->GetCurrentLocation().GetY().GetUnderlying(),
          });
    }

    return std::move(response);
  }

 private:
  SharedRef<core::ports::ICourierRepository> const courier_repository_;
};

}  // namespace

auto MakeGetCouriersHandler(
    SharedRef<core::ports::ICourierRepository> courier_repository)
    -> SharedRef<IGetCouriersHandler> {
  return userver::utils::MakeSharedRef<const GetCouriersHandler>(
      std::move(courier_repository));
}

}  // namespace delivery::core::application::use_cases::queries::get_couriers
