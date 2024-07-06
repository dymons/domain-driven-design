from microservices.delivery.tests.delivery.fixtures.api_v1_couriers import api_v1_couriers
from microservices.delivery.tests.delivery.fixtures.courier_repository import courier_repository


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
        ('id', 'name', 'not_available', '(1, "pedestrian", 1, 1)', '(1,1)'),
    ])

    # Act
    response = await api_v1_couriers.execute()

    # Assert
    assert response.status == 200
    assert response.json() == {'couriers': [
        {'id': 'id', 'location': {'x': 1, 'y': 1}, 'name': 'name'},
    ]}
