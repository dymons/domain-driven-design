#pragma once

#include <optional>

#include <core/domain_services/dispatch_service/iservice.hpp>
#include <core/ports/icourier_repository.hpp>
#include <core/ports/iorder_repository.hpp>
#include <utils/memory.hpp>

#include "command.hpp"

namespace delivery::core::application::use_cases::commands::assign_orders {

class AssignOrdersHandler final {
  SharedRef<core::ports::ICourierRepository> courier_repository_;
  SharedRef<core::ports::IOrderRepository> order_repository_;
  SharedRef<core::domain_services::IDispatchService> dispatch_service_;

 public:
  AssignOrdersHandler(SharedRef<core::ports::ICourierRepository>,
                      SharedRef<core::ports::IOrderRepository>,
                      SharedRef<core::domain_services::IDispatchService>);

  auto Handle(AssignOrdersCommand&&) -> void;
};

}  // namespace delivery::core::application::use_cases::commands::assign_orders
