#pragma once

#include <string>

namespace delivery::core::domain::order {

class OrderStatus {
  enum class Status {
    Created,
    Assigned,
    Completed,
  };

  // Constructors

  explicit OrderStatus(Status status);

 public:
  static const OrderStatus kCreated;
  static const OrderStatus kAssigned;
  static const OrderStatus kCompleted;

  [[nodiscard]] static auto FromString(std::string_view) -> OrderStatus;
  [[nodiscard]] auto ToString() const -> std::string;

  // Observers

  [[nodiscard]] auto IsCreated() const noexcept -> bool;
  [[nodiscard]] auto IsAssigned() const noexcept -> bool;
  [[nodiscard]] auto IsCompleted() const noexcept -> bool;

  auto operator<=>(OrderStatus const&) const = default;

 private:
  Status status_;
};

}  // namespace delivery::core::domain::order
