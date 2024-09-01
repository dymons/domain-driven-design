import operator

from microservices.delivery.tests.delivery.fixtures.api_v1_couriers import api_v1_couriers
from microservices.delivery.tests.delivery.fixtures.courier_repository import courier_repository
from microservices.delivery.tests.delivery.utils.types import Defaults
from microservices.delivery.tests.delivery.utils.types import make_courier


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
        make_courier(id=Defaults.courier_id + '_1'),
        make_courier(id=Defaults.courier_id + '_2'),
    ])

    # Act
    response = await api_v1_couriers.execute()

    # Assert
    assert response.status == 200
    response.json()['couriers'].sort(key=operator.itemgetter('id'))
    assert response.json() == {
        'couriers': [
            {
                'id': Defaults.courier_id + '_1',
                'location': Defaults.delivery_location,
                'name': Defaults.courier_name,
            },
            {
                'id': Defaults.courier_id + '_2',
                'location': Defaults.delivery_location,
                'name': Defaults.courier_name,
            },
        ],
    }
