#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/ports/icourier_repository.hpp>

namespace delivery::core::application::use_cases::commands::stop_work {

namespace {

class StartWorkHandler final : public IStopWorkHandler {
 public:
  ~StartWorkHandler() final = default;

  StartWorkHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository)
      : courier_repository_(std::move(courier_repository)) {}

  auto Handle(StopWorkCommand&& command) const -> void final try {
    auto courier = courier_repository_->GetById(
        domain::courier::CourierId{command.GetCourierId()});

    try {
      courier->StopWork();
    } catch (domain::courier::TryStartWorkingWhenAlreadyStarted const&) {
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
  return userver::utils::MakeSharedRef<const StartWorkHandler>(
      std::move(courier_repository));
}

}  // namespace delivery::core::application::use_cases::commands::stop_work
