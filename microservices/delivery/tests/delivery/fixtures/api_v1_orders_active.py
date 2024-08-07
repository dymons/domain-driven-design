import pytest

from typing import Dict
from typing import Any


def default_api_v1_orders_active_request() -> Dict[str, Any]:
    return {}


@pytest.fixture
async def api_v1_orders_active(
        service_client,
):
    class Context:
        def __init__(self):
            self.request = default_api_v1_orders_active_request()

        async def execute(self):
            return await service_client.get('/api/v1/orders/active', json=self.request)

    return Context()
