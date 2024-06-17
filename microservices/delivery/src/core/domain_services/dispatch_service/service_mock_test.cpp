#include "service_mock_test.hpp"

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
      std::unordered_set<MutableSharedRef<domain::courier::Courier>>&&) const
      -> DispatchResult final {
    return dispatch_result_;
  }

 private:
  IDispatchService::DispatchResult dispatch_result_;
};

}  // namespace

auto MockDispatchService(IDispatchService::DispatchResult dispatch_result)
    -> SharedRef<IDispatchService> {
  return userver::utils::MakeSharedRef<const DispatchService>(
      std::move(dispatch_result));
}

}  // namespace delivery::core::domain_services
