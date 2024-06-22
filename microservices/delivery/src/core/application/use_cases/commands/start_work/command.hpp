#pragma once

#include <string>

namespace delivery::core::application::use_cases::commands::start_work {

class StartWorkCommand final {
  std::string courier_id_;

 public:
  explicit StartWorkCommand(std::string courier_id);

  [[nodiscard]] auto GetCourierId() const noexcept -> std::string;
};

}  // namespace delivery::core::application::use_cases::commands::start_work
