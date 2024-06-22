#include "response.hpp"

namespace delivery::core::application::use_cases::queries::get_couriers {

Courier::Courier(std::string id, std::string name, Location location)
    : id_{std::move(id)}, name_{std::move(name)}, location_{location} {}

auto Courier::GetId() const noexcept -> std::string { return id_; }

auto Courier::GetName() const noexcept -> std::string { return name_; }

auto Courier::GetLocation() const noexcept -> Location { return location_; }

}  // namespace delivery::core::application::use_cases::queries::get_couriers
