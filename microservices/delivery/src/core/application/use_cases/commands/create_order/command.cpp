#include "command.hpp"

#include <core/application/exceptions.hpp>

namespace delivery::application::use_cases::commands::create_order {

CreateOrderCommand::CreateOrderCommand(std::string basket_id,
                                       std::string address, int weight) {
  if (basket_id.empty()) {
    throw ArgumentException{"basket_id is empty"};
  }

  if (address.empty()) {
    throw ArgumentException{"address is empty"};
  }

  if (weight < 0) {
    throw ArgumentException{"weight should be positive"};
  }

  basket_id_ = std::move(basket_id);
  address_ = std::move(address);
  weight_ = weight;
}

auto CreateOrderCommand::GetBasketId() const noexcept -> std::string {
  return basket_id_;
}

auto CreateOrderCommand::GetAddress() const noexcept -> std::string {
  return address_;
}

auto CreateOrderCommand::GetWeight() const noexcept -> int { return weight_; }

}  // namespace delivery::application::use_cases::commands::create_order
