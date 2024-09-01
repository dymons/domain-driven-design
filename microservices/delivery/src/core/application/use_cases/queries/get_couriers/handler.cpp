#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/ports/courier_repository/irepository.hpp>
#include <utils/ranges.hpp>

#include "ihandler.hpp"
#include "query.hpp"
#include "response.hpp"

namespace delivery::core::application::use_cases::queries::get_couriers {

namespace {

Courier ConvertCourier(SharedRef<domain::courier::Courier> const& courier) {
  return {
      .id = courier->GetId().GetUnderlying(),
      .name = courier->GetName().GetUnderlying(),
      .location{
          .x = courier->GetCurrentLocation().GetX().GetUnderlying(),
          .y = courier->GetCurrentLocation().GetY().GetUnderlying(),
      },
  };
}

class GetCouriersHandler final : public IGetCouriersHandler {
 public:
  ~GetCouriersHandler() final = default;

  explicit GetCouriersHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository)
      : courier_repository_{std::move(courier_repository)} {}

  [[nodiscard]] auto Handle(GetCouriersQuery&&) const
      -> std::vector<Courier> final {
    return courier_repository_->GetCouriers()       //
           | std::views::transform(ConvertCourier)  //
           | ranges::to<std::vector>();
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
