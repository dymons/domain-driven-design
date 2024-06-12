#pragma once

#include <optional>

#include <core/domain_services/idispatch_service.hpp>
#include <core/ports/icourier_repository.hpp>
#include <core/ports/iorder_repository.hpp>
#include <utils/memory.hpp>

#include "command.hpp"

namespace delivery::application::use_cases::commands::assign_orders {

class Handler {
  SharedRef<core::ports::ICourierRepository> courier_repository_;
  SharedRef<core::ports::IOrderRepository> order_repository_;
  SharedRef<core::domain_services::IDispatchService> dispatch_service_;

 public:
  Handler(SharedRef<core::ports::ICourierRepository>,
          SharedRef<core::ports::IOrderRepository>,
          SharedRef<core::domain_services::IDispatchService>);

  auto Handle(Command) -> void;
};

}  // namespace delivery::application::use_cases::commands::assign_orders
