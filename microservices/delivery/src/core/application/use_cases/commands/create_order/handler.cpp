#include "handler.hpp"

#include <core/domain/order/order.hpp>
#include <core/ports/order_repository/irepository.hpp>

#include "command.hpp"
#include "ihandler.hpp"

namespace delivery::core::application::use_cases::commands::create_order {

namespace {

class CreateOrderHandler final : public ICreateOrderHandler {
 public:
  ~CreateOrderHandler() final = default;

  explicit CreateOrderHandler(
      SharedRef<core::ports::IOrderRepository> order_repository)
      : order_repository_{std::move(order_repository)} {}

  auto Handle(CreateOrderCommand&& command) const -> void final {
    auto const order = core::domain::order::Order::Create(
        core::domain::order::BasketId{command.GetBasketId()},
        core::domain::Location::kMinLocation,
        core::domain::Weight{command.GetWeight()});

    try {
      order_repository_->Add(order);
    } catch (core::ports::OrderAlreadyExists const&) {
    }
  }

 private:
  SharedRef<core::ports::IOrderRepository> const order_repository_;
};

}  // namespace

auto MakeCreateOrderHandler(
    SharedRef<core::ports::IOrderRepository> order_repository)
    -> SharedRef<ICreateOrderHandler> {
  return delivery::MakeSharedRef<CreateOrderHandler>(
      std::move(order_repository));
}

}  // namespace delivery::core::application::use_cases::commands::create_order
