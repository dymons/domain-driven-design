from microservices.delivery.tests.fixtures import api_v1_orders


async def test_basic(api_v1_orders):
    response = await api_v1_orders.execute()
    assert response.status == 200
