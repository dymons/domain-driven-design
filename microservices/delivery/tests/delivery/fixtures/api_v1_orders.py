import pytest

from typing import Dict
from typing import Any

from microservices.delivery.tests.delivery.utils.types import default_basket_id


def default_api_v1_orders_request(
        basket_id: str = default_basket_id(),
        address: str = 'address',
        weight: int = 1,
) -> Dict[str, Any]:
    return {
        'basket_id': basket_id,
        'address': address,
        'weight': weight,
    }


@pytest.fixture
async def api_v1_orders(
        service_client,
):
    class Context:
        def __init__(self):
            self.request = default_api_v1_orders_request()

        async def execute(self):
            return await service_client.post('/api/v1/orders', json=self.request)

    return Context()
