import operator

from microservices.delivery.tests.delivery.fixtures.api_v1_orders_active import api_v1_orders_active
from microservices.delivery.tests.delivery.fixtures.order_repository import order_repository
from microservices.delivery.tests.delivery.utils.types import make_order
from microservices.delivery.tests.delivery.utils.types import Defaults


async def test_empty_orders(
        api_v1_orders_active,
):
    # Arrange & Act
    response = await api_v1_orders_active.execute()

    # Assert
    assert response.status == 200
    assert response.json() == {'orders': []}


async def test_given_non_empty_orders_when_get_active_orders_then_active_orders_are_received(
        api_v1_orders_active,
        order_repository,
):
    # Arrange
    order_repository.insert_orders([
        make_order(id=Defaults.basket_id + '_1'),
        make_order(id=Defaults.basket_id + '_2'),
        make_order(id=Defaults.basket_id + '_3', status='completed'),
    ])

    # Act
    response = await api_v1_orders_active.execute()

    # Assert
    assert response.status == 200
    response.json()['orders'].sort(key=operator.itemgetter('id'))
    assert response.json() == {'orders': [
        {
            'id': Defaults.basket_id + '_1',
            'location': Defaults.delivery_location,
        },
        {
            'id': Defaults.basket_id + '_2',
            'location': Defaults.delivery_location,
        },
    ]}
