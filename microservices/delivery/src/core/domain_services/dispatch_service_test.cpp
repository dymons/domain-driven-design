#include <userver/utest/utest.hpp>

#include <core/domain/courier/courier_mock_test.hpp>
#include <core/domain/order/order_mock_test.hpp>
#include "dispatch_service.hpp"
#include "idispatch_service.hpp"

namespace delivery::core::domain_services {

namespace {

UTEST(DispatchServiceShould, DispatchCourier) {
  // Arrange
  auto const dispatcher = MakeDispatchService();
  auto order = domain::order::MockOrder();
  auto const courier = domain::courier::MockCourier();

  // Act
  order = dispatcher->Dispatch(std::move(order), {courier});

  // Assert
  ASSERT_TRUE(order.IsCourierAssigned());
  ASSERT_EQ(order.GetCourierId(),
            domain::order::CourierId{courier.GetId().GetUnderlying()});
}

UTEST(DispatchServiceShould, NotDispatchWhenNotReadyCouriers) {
  // Arrange
  auto const dispatcher = MakeDispatchService();
  auto order = domain::order::MockOrder();
  auto couriers = std::unordered_set<domain::courier::Courier>{};

  // Act
  order = dispatcher->Dispatch(std::move(order), couriers);

  // Assert
  ASSERT_FALSE(order.IsCourierAssigned());
}

}  // namespace

}  // namespace delivery::core::domain_services
