#include "response.hpp"

// clang-format off
namespace delivery::core::application::use_cases::queries::get_active_orders {
// clang-format on

Location::Location(int x, int y) : x_{x}, y_{y} {}

auto Location::GetX() const noexcept -> int { return x_; }

auto Location::GetY() const noexcept -> int { return y_; }

Order::Order(std::string id, Location location)
    : id_{std::move(id)}, location_{location} {}

auto Order::GetId() const noexcept -> std::string { return id_; }

auto Order::GetLocation() const noexcept -> Location { return location_; }

// clang-format off
}  // namespace delivery::core::application::use_cases::queries::get_active_orders
// clang-format on
