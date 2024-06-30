import pytest
import psycopg2


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


@pytest.fixture
async def orders_repository(pgsql):
    class Context:
        # noinspection PyMethodMayBeStatic
        def execute(self, query):
            cursor = pgsql['20240526213109_init'].cursor()
            try:
                cursor.execute(query)
                return cursor.fetchall()
            finally:
                cursor.close()

    return Context()
