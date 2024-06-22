#pragma once

#include <variant>

namespace delivery::core::application::use_cases::queries::get_orders {

struct Response200 {

};

using Response = std::variant<Response200>;

} // namespace delivery::core::application::use_cases::queries::get_orders
