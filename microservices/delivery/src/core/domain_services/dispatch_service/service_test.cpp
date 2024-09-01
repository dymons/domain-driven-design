#include <userver/utest/utest.hpp>

#include <core/domain/courier/courier_mock.hpp>
#include <core/domain/order/order_mock.hpp>

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
  ASSERT_EQ(result.order->GetCourierId(), courier->GetId());
}

UTEST(DispatchServiceShould, NotDispatchWhenNotReadyCouriers) {
  // Arrange
  auto const dispatcher = MakeDispatchService();
  auto order = domain::order::MockOrder();
  auto couriers = std::vector<MutableSharedRef<domain::courier::Courier>>{};

  // Act
  auto result = dispatcher->Dispatch(std::move(order), std::move(couriers));

  // Assert
  ASSERT_FALSE(result.order->IsCourierAssigned());
}

}  // namespace

}  // namespace delivery::core::domain_services
