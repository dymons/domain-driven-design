#pragma once

#include <optional>

#include <core/ports/iorder_repository.hpp>
#include <utils/memory.hpp>

#include "command.hpp"

namespace delivery::application::use_cases::commands::create_order {

class Handler {
  SharedRef<core::ports::IOrderRepository> order_repository_;

 public:
  explicit Handler(SharedRef<core::ports::IOrderRepository>);

  auto Handle(Command&&) -> void;
};

}  // namespace delivery::application::use_cases::commands::create_order
