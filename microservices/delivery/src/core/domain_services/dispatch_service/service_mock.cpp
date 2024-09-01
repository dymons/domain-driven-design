#include "service_mock.hpp"

#include <core/domain/courier/courier.hpp>
#include <core/domain/order/order.hpp>

namespace delivery::core::domain_services {

namespace {

class DispatchService final : public IDispatchService {
 public:
  ~DispatchService() final = default;

  DispatchService(IDispatchService::DispatchResult dispatch_result)
      : dispatch_result_{std::move(dispatch_result)} {}

  [[nodiscard]] auto Dispatch(
      MutableSharedRef<domain::order::Order>&&,
      std::vector<MutableSharedRef<domain::courier::Courier>>&&) const
      -> DispatchResult final {
    return dispatch_result_;
  }

 private:
  IDispatchService::DispatchResult dispatch_result_;
};

}  // namespace

auto MockDispatchService(IDispatchService::DispatchResult dispatch_result)
    -> SharedRef<IDispatchService> {
  return delivery::MakeSharedRef<DispatchService>(std::move(dispatch_result));
}

}  // namespace delivery::core::domain_services
