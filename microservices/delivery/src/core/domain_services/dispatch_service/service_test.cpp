#include <userver/utest/utest.hpp>

#include <core/domain/courier/courier_mock_test.hpp>
#include <core/domain/order/order_mock_test.hpp>

#include "iservice.hpp"
#include "service.hpp"

namespace delivery::core::domain_services {

namespace {

UTEST(DispatchServiceShould, DispatchCourier) {
  // Arrange
  auto const dispatcher = MakeDispatchService();
  auto order = domain::order::MockOrder();
  auto const courier = domain::courier::MockCourier();

  // Act
  auto result = dispatcher->Dispatch(std::move(order), {courier});

  // Assert
  ASSERT_TRUE(result.order->IsCourierAssigned());
  ASSERT_EQ(result.order->GetCourierId(),
            domain::order::CourierId{courier->GetId().GetUnderlying()});
}

UTEST(DispatchServiceShould, NotDispatchWhenNotReadyCouriers) {
  // Arrange
  auto const dispatcher = MakeDispatchService();
  auto order = domain::order::MockOrder();
  auto couriers =
      std::unordered_set<MutableSharedRef<domain::courier::Courier>>{};

  // Act
  auto result = dispatcher->Dispatch(std::move(order), std::move(couriers));

  // Assert
  ASSERT_FALSE(result.order->IsCourierAssigned());
}

}  // namespace

}  // namespace delivery::core::domain_services
