#pragma once

#include <core/ports/iorder_repository.hpp>
#include <utils/memory.hpp>

#include "command.hpp"

namespace delivery::core::application::use_cases::commands::create_order {

class CreateOrderHandler final {
  SharedRef<core::ports::IOrderRepository> order_repository_;

 public:
  explicit CreateOrderHandler(SharedRef<core::ports::IOrderRepository>);

  auto Handle(CreateOrderCommand&&) const -> void;
};

}  // namespace delivery::core::application::use_cases::commands::api_v1_orders
