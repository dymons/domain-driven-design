#pragma once

#include <string_view>

namespace delivery::core::domain::courier {

class CourierStatus {
 public:
  enum class Status {
    NotAvailable,
    Ready,
    Busy,
  };

  explicit CourierStatus(Status status);

  static auto FromString(std::string_view status) -> CourierStatus;
  auto ToString() const -> std::string;

  auto IsNotAvailable() const noexcept -> bool;
  auto IsReady() const noexcept -> bool;
  auto IsBusy() const noexcept -> bool;

 private:
  Status status_;
};

}  // namespace delivery::core::domain::courier
