import pytest


@pytest.fixture
async def order_repository(pgsql):
    class Context:
        def __init__(self):
            self._db = '20240526213109_init'

        def get_orders(self):
            cursor = pgsql[self._db].cursor()
            try:
                cursor.execute('SELECT * FROM delivery.orders')
                return cursor.fetchall()
            finally:
                cursor.close()

    return Context()
