import operator


from microservices.delivery.tests.delivery.fixtures.api_v1_couriers import api_v1_couriers
from microservices.delivery.tests.delivery.fixtures.courier_repository import courier_repository
from microservices.delivery.tests.delivery.fixtures.courier_repository import Courier
from microservices.delivery.tests.delivery.utils.types import *


async def test_empty_couriers(
        api_v1_couriers,
):
    # Arrange & Act
    response = await api_v1_couriers.execute()

    # Assert
    assert response.status == 200
    assert response.json() == {'couriers': []}


async def test_given_non_empty_couriers_when_get_couriers_then_couriers_are_received(
        api_v1_couriers,
        courier_repository,
):
    # Arrange
    courier_repository.insert_couriers([
        Courier(id=CourierId(default_courier_id() + '_1')),
        Courier(id=CourierId(default_courier_id() + '_2')),
    ])

    # Act
    response = await api_v1_couriers.execute()

    # Assert
    assert response.status == 200
    response.json()['couriers'].sort(key=operator.itemgetter('id'))
    assert response.json() == {
        'couriers': [
            {
                'id': default_courier_id() + '_2',
                'location': default_location(),
                'name': default_courier_name(),
            },
            {
                'id': default_courier_id() + '_1',
                'location': default_location(),
                'name': default_courier_name(),
            },
        ],
    }
