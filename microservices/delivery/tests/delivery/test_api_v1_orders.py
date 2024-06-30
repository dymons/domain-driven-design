from microservices.delivery.tests.fixtures import api_v1_orders
from microservices.delivery.tests.fixtures import order_repository
from microservices.delivery.tests.requests import fake_basket_id


async def test_given_empty_orders_when_create_order_then_order_is_created(
        api_v1_orders,
        order_repository,
):
    # Arrange & Act
    response = await api_v1_orders.execute()

    # Assert
    assert response.status == 200
    assert order_repository.get_orders() == [
        (fake_basket_id(), 'created', None, '(1,1)', '(1)'),
    ]


async def test_given_empty_orders_when_create_same_order_several_times_then_order_is_created_once(
        api_v1_orders,
        order_repository,
):
    # Arrange & Act
    response_first = await api_v1_orders.execute()
    response_second = await api_v1_orders.execute()

    # Assert
    assert response_first.status == 200
    assert response_second.status == 200
    assert order_repository.get_orders() == [
        (fake_basket_id(), 'created', None, '(1,1)', '(1)'),
    ]
