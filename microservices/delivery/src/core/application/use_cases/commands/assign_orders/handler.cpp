#include "handler.hpp"

#include <algorithm>
#include <ranges>

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>

namespace delivery::application::use_cases::commands::assign_orders {

Handler::Handler(
    SharedRef<core::ports::ICourierRepository> courier_repository,
    SharedRef<core::ports::IOrderRepository> order_repository,
    SharedRef<core::domain_services::IDispatchService> dispatch_service)
    : courier_repository_(std::move(courier_repository)),
      order_repository_(std::move(order_repository)),
      dispatch_service_(std::move(dispatch_service)) {}

auto Handler::Handle(Command) -> void {
  auto orders = order_repository_->GetNotAssigned();

  orders | std::ranges::views::take(1) |
      std::ranges::views::transform([this](auto order) {
        auto const couriers = courier_repository_->GetByReadyStatus();
        return dispatch_service_->Dispatch(std::move(order), couriers);
      });
}

}  // namespace delivery::application::use_cases::commands::assign_orders
