#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/ports/courier_repository/irepository.hpp>

#include "ihandler.hpp"
#include "query.hpp"
#include "response.hpp"

namespace delivery::core::application::use_cases::queries::get_couriers {

namespace {

class GetCouriersHandler final : public IGetCouriersHandler {
 public:
  ~GetCouriersHandler() final = default;

  explicit GetCouriersHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository)
      : courier_repository_(std::move(courier_repository)) {}

  [[nodiscard]] auto Handle(GetCouriersQuery&&) const
      -> std::vector<Courier> final {
    auto couriers = courier_repository_->GetCouriers();

    auto result = std::vector<Courier>{};
    result.reserve(couriers.size());
    for (auto&& courier : couriers) {
      result.emplace_back(
          courier->GetId().GetUnderlying(), courier->GetName().GetUnderlying(),
          Location{courier->GetCurrentLocation().GetX().GetUnderlying(),
                   courier->GetCurrentLocation().GetY().GetUnderlying()});
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
