import pytest

from typing import Dict
from typing import Any


def default_api_v1_couriers_request() -> Dict[str, Any]:
    return {}


@pytest.fixture
async def api_v1_couriers(
        service_client,
):
    class Context:
        def __init__(self):
            self.request = default_api_v1_couriers_request()

        async def execute(self):
            return await service_client.post('/api/v1/couriers', json=self.request)

    return Context()
