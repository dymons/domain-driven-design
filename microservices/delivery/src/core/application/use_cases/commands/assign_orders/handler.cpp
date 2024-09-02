#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>
#include <core/domain_services/dispatch_service/iservice.hpp>
#include <core/ports/courier_repository/irepository.hpp>
#include <core/ports/order_repository/irepository.hpp>
#include <core/ports/unit_of_work/irun_transaction_context.hpp>
#include <core/ports/unit_of_work/iunit_of_work.hpp>
#include <utils/container.hpp>
#include <utils/optional.hpp>

#include "command.hpp"
#include "ihandler.hpp"

namespace delivery::core::application::use_cases::commands::assign_orders {

namespace {

class AssignOrdersHandler final : public IAssignOrdersHandler {
 public:
  ~AssignOrdersHandler() final = default;

  AssignOrdersHandler(
      SharedRef<core::ports::ICourierRepository> courier_repository,
      SharedRef<core::ports::IOrderRepository> order_repository,
      SharedRef<core::ports::IUnitOfWork> unit_of_work,
      SharedRef<core::domain_services::IDispatchService> dispatch_service)
      : courier_repository_{std::move(courier_repository)},
        order_repository_{std::move(order_repository)},
        unit_of_work_{std::move(unit_of_work)},
        dispatch_service_{std::move(dispatch_service)} {}

  auto Handle(AssignOrdersCommand&&) const -> void final {
    auto const dispatch_view =
        container::FirstOrNullopt(order_repository_->GetNotAssigned())
            .transform([this](auto&& order) {
              auto couriers = courier_repository_->GetByReadyStatus();
              return this->dispatch_service_->Dispatch(
                  std::forward<decltype(order)>(order), std::move(couriers));
            });

    optional::map(dispatch_view, [this](auto const& dispatch) {
      this->unit_of_work_->RunTransaction([&](auto const& context) {
        context->GetOrderRepository()->Update(dispatch.order);
        optional::map(dispatch.courier, [&](auto const& courier) {
          context->GetCourierRepository()->Update(courier);
        });
      });
    });
  }

 private:
  SharedRef<core::ports::ICourierRepository> const courier_repository_;
  SharedRef<core::ports::IOrderRepository> const order_repository_;
  SharedRef<core::ports::IUnitOfWork> const unit_of_work_;
  SharedRef<core::domain_services::IDispatchService> const dispatch_service_;
};

}  // namespace

auto MakeAssignOrdersHandler(
    SharedRef<core::ports::ICourierRepository> courier_repository,
    SharedRef<core::ports::IOrderRepository> order_repository,
    SharedRef<core::ports::IUnitOfWork> unit_of_work,
    SharedRef<core::domain_services::IDispatchService> dispatch_service)
    -> SharedRef<IAssignOrdersHandler> {
  return delivery::MakeSharedRef<AssignOrdersHandler>(
      std::move(courier_repository), std::move(order_repository),
      std::move(unit_of_work), std::move(dispatch_service));
}

}  // namespace delivery::core::application::use_cases::commands::assign_orders
