import pytest


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
