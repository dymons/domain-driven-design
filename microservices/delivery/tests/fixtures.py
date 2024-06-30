import pytest


from microservices.delivery.tests.requests import get_api_v1_orders_request


@pytest.fixture
async def api_v1_orders(
        service_client,
):
    request = get_api_v1_orders_request()

    class Context:
        def __init__(self):
            pass

        # noinspection PyMethodMayBeStatic
        async def execute(self):
            return await service_client.post('/api/v1/orders', json=request)

    return Context()
