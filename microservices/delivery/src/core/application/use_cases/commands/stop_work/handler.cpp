#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/ports/courier_repository/irepository.hpp>

#include "command.hpp"
#include "ihandler.hpp"

namespace delivery::core::application::use_cases::commands::stop_work {

namespace {

class StartWorkHandler final : public IStopWorkHandler {
 public:
  ~StartWorkHandler() final = default;

  explicit StartWorkHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository)
      : courier_repository_{std::move(courier_repository)} {}

  auto Handle(StopWorkCommand&& command) const -> void final try {
    auto courier =
        courier_repository_->GetById(domain::CourierId{command.GetCourierId()});

    try {
      courier->StopWork();
    } catch (domain::courier::TryStopWorkingWithIncompleteDelivery const&) {
      // TODO (dymons) Return 200/202
    }

    courier_repository_->Update(courier);
  } catch (ports::CourierNotFound const&) {
    // TODO (dymons) Return 404
  }

 private:
  SharedRef<core::ports::ICourierRepository> const courier_repository_;
};

}  // namespace

auto MakeStopWorkHandler(
    SharedRef<core::ports::ICourierRepository> courier_repository)
    -> SharedRef<IStopWorkHandler> {
  return delivery::MakeSharedRef<StartWorkHandler>(
      std::move(courier_repository));
}

}  // namespace delivery::core::application::use_cases::commands::stop_work
