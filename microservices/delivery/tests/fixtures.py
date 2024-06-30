import pytest


from microservices.delivery.tests.requests import default_api_v1_orders_request


@pytest.fixture
async def api_v1_orders(
        service_client,
):
    class Context:
        def __init__(self):
            self.request = default_api_v1_orders_request()

        # noinspection PyMethodMayBeStatic
        async def execute(self):
            return await service_client.post('/api/v1/orders', json=self.request)

    return Context()


@pytest.fixture
async def order_repository(pgsql):
    class Context:
        def __init__(self):
            pass

        # noinspection PyMethodMayBeStatic
        def get_orders(self):
            cursor = pgsql['20240526213109_init'].cursor()
            try:
                cursor.execute('SELECT * FROM delivery.orders')
                return cursor.fetchall()
            finally:
                cursor.close()

    return Context()
