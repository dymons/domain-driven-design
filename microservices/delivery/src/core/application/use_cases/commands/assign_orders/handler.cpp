#include "handler.hpp"

#include <algorithm>
#include <ranges>

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>
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
  auto couriers = courier_repository_->GetByReadyStatus();
  auto const orders = order_repository_->GetNotAssigned();

  auto const dispatch_view =
      orders | std::ranges::views::take(1) |
      std::ranges::views::transform([&couriers, this](auto order) {
        return this->dispatch_service_->Dispatch(std::move(order),
                                                 std::move(couriers));
      });

  std::ranges::for_each(dispatch_view, [this](auto const& dispatch) {
    // TODO (dymons) Use UnitOfWork
    this->order_repository_->Update(dispatch.order);
    optional::map(dispatch.courier, [this](const auto& courier) {
      this->courier_repository_->Update(courier);
    });
  });
}

}  // namespace delivery::application::use_cases::commands::assign_orders
