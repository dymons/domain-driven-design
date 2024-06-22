#include "response.hpp"

namespace delivery::core::application::use_cases::queries::get_orders {

Location::Location(int x, int y) : x_{x}, y_{y} {}

auto Location::GetX() const noexcept -> int { return x_; }

auto Location::GetY() const noexcept -> int { return y_; }

Order::Order(std::string id, Location location)
    : id_{std::move(id)}, location_{location} {}

auto Order::GetId() const noexcept -> std::string { return id_; }

auto Order::GetLocation() const noexcept -> Location { return location_; }

}  // namespace delivery::core::application::use_cases::queries::get_orders
