#pragma once

#include <string>

#include <utils/refinement_type/not_empty.hpp>
#include <utils/refinement_type/refinement_type.hpp>
#include <utils/refinement_type/should_be_positive.hpp>

namespace delivery::application::use_cases::commands::create_order {

using BacketId = RefinementType<struct BacketIdTag, std::string, NotEmpty>;
using Address = RefinementType<struct AddressTag, std::string, NotEmpty>;
using Weight = RefinementType<struct WeightTag, int, ShouldBePositive>;

struct CreateOrderCommand final {
  BacketId basket_id;
  std::string address;
  Weight weight;
};

}  // namespace delivery::application::use_cases::commands::create_order
