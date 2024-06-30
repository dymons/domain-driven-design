from microservices.delivery.tests.fixtures import api_v1_orders


async def test_given_empty_orders_when_create_order_then_order_is_created(
        api_v1_orders,
):
    # Arrange & Act
    response = await api_v1_orders.execute()

    # Assert
    assert response.status == 200
