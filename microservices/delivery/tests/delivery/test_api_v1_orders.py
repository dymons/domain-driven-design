from microservices.delivery.tests.fixtures import api_v1_orders
from microservices.delivery.tests.fixtures import orders_repository


async def test_given_empty_orders_when_create_order_then_order_is_created(
        api_v1_orders,
        orders_repository,
):
    # Arrange & Act
    response = await api_v1_orders.execute()

    # Assert
    assert response.status == 200

    orders = orders_repository.execute('SELECT * FROM delivery.orders')
    assert orders == [('basket_id', 'created', None, '(1,1)', '(1)')]
