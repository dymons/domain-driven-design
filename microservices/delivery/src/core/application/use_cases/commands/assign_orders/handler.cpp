#include "handler.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>
#include <utils/container.hpp>
#include <utils/optional.hpp>

namespace delivery::application::use_cases::commands::assign_orders {

AssignOrdersHandler::AssignOrdersHandler(
    SharedRef<core::ports::ICourierRepository> courier_repository,
    SharedRef<core::ports::IOrderRepository> order_repository,
    SharedRef<core::domain_services::IDispatchService> dispatch_service)
    : courier_repository_(std::move(courier_repository)),
      order_repository_(std::move(order_repository)),
      dispatch_service_(std::move(dispatch_service)) {}

auto AssignOrdersHandler::Handle(AssignOrdersCommand&&) -> void {
  auto const dispatch_view =
      container::FirstOrNullopt(order_repository_->GetNotAssigned())
          .transform([this](auto&& order) {
            auto couriers = courier_repository_->GetByReadyStatus();
            return this->dispatch_service_->Dispatch(
                std::forward<decltype(order)>(order), std::move(couriers));
          });

  optional::map(dispatch_view, [this](auto const& dispatch) {
    // TODO (dymons) Use UnitOfWork
    this->order_repository_->Update(dispatch.order);
    optional::map(dispatch.courier, [this](auto const& courier) {
      this->courier_repository_->Update(courier);
    });
  });
}

}  // namespace delivery::application::use_cases::commands::assign_orders
