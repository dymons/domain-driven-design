#pragma once

#include <string>

namespace delivery::core::application::use_cases::commands::stop_work {

class StopWorkCommand final {
  std::string courier_id_;

 public:
  explicit StopWorkCommand(std::string courier_id);

  [[nodiscard]] auto GetCourierId() const noexcept -> std::string;
};

}  // namespace delivery::core::application::use_cases::commands::stop_work
