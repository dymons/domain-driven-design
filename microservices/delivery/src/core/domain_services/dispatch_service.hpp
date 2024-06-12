#pragma once

#include "idispatch_service.hpp"

namespace delivery::core::domain_services {

class DispatchService final : public IDispatchService {
 public:
  ~DispatchService() final = default;

  auto Dispatch(domain::order::Order&&,
                std::vector<domain::courier::Courier> const&)
      -> domain::order::Order final;
};

}  // namespace delivery::core::domain_services
