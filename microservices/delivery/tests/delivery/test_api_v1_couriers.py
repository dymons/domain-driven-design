from microservices.delivery.tests.delivery.fixtures.api_v1_couriers import api_v1_couriers
from microservices.delivery.tests.delivery.fixtures.courier_repository import courier_repository


async def test_empty_couriers(
        api_v1_couriers,
        courier_repository,
):
    # Arrange & Act
    response = await api_v1_couriers.execute()

    # Assert
    assert response.status == 200
    # assert order_repository.get_orders() == [
    #     (default_basket_id(), 'created', None, '(1,1)', '(1)'),
    # ]