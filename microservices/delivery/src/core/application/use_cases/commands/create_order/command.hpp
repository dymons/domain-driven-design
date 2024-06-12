#pragma once

#include <string>

namespace delivery::application::use_cases::commands::create_order {

class CreateOrderCommand final {
  std::string basket_id_;
  std::string address_;
  int weight_;

 public:
  CreateOrderCommand(std::string basket_id, std::string address, int weight);

  [[nodiscard]] auto GetBasketId() const noexcept -> std::string;
  [[nodiscard]] auto GetAddress() const noexcept -> std::string;
  [[nodiscard]] auto GetWeight() const noexcept -> int;
};

}  // namespace delivery::application::use_cases::commands::create_order
