from microservices.delivery.tests.delivery.fixtures.api_v1_orders_active import api_v1_orders_active


async def test_empty_orders(
        api_v1_orders_active,
):
    # Arrange & Act
    response = await api_v1_orders_active.execute()

    # Assert
    assert response.status == 200
    assert response.json() == {'orders': []}
