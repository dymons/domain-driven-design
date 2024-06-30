import pytest


@pytest.fixture
async def api_v1_orders(
        service_client,
):
    request = {
        'basket_id': 'basket_id1',
        'address': 'address',
        'weight': 1,
    }

    class Context:
        # noinspection PyMethodMayBeStatic
        async def execute(self):
            return await service_client.post('/api/v1/orders', json=request)

    return Context()
