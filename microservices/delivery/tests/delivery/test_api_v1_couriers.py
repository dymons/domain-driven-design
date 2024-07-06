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
