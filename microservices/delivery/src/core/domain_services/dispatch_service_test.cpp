#include <userver/utest/utest.hpp>

#include <core/domain/courier/courier_mock_test.hpp>
#include <core/domain/order/order_mock_test.hpp>
#include "dispatch_service.hpp"
#include "idispatch_service.hpp"

namespace delivery::core::domain_services {

namespace {

UTEST(DispatchServiceShould, NotDispatchWhenNotReadyCouriers) {
  // Arrange
  auto const dispatcher = MakeDispatchService();
  auto order = domain::order::MockOrder();
  auto couriers = std::vector<domain::courier::Courier>{};

  // Act
  order = dispatcher->Dispatch(std::move(order), couriers);

  // Assert
  ASSERT_FALSE(order.IsCourierAssigned());
}

}  // namespace

}  // namespace delivery::core::domain_services
