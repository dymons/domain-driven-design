#pragma once

#include <string_view>

namespace delivery::core::domain::courier {

class CourierStatus final {
  enum class Status {
    NotAvailable,
    Ready,
    Busy,
  };

  // Constructors

  explicit CourierStatus(Status status);

 public:
  static const CourierStatus kNotAvailable;
  static const CourierStatus kReady;
  static const CourierStatus kBusy;

  [[nodiscard]] static auto FromString(std::string_view) -> CourierStatus;
  [[nodiscard]] auto ToString() const -> std::string;

  // Observers

  [[nodiscard]] auto IsNotAvailable() const noexcept -> bool;
  [[nodiscard]] auto IsReady() const noexcept -> bool;
  [[nodiscard]] auto IsBusy() const noexcept -> bool;

  auto operator<=>(CourierStatus const&) const = default;

 private:
  Status status_;
};

}  // namespace delivery::core::domain::courier
