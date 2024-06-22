#include "command.hpp"

#include <userver/utils/exception.hpp>

#include <core/application/exceptions.hpp>

namespace delivery::core::application::use_cases::commands::start_work {

StartWorkCommand::StartWorkCommand(std::string courier_id) {
  if (courier_id.empty()) {
    userver::utils::LogErrorAndThrow<ArgumentException>("courier_id is empty");
  }

  courier_id_ = std::move(courier_id);
}

auto StartWorkCommand::GetCourierId() const noexcept -> std::string {
  return courier_id_;
}

}  // namespace delivery::core::application::use_cases::commands::start_work
