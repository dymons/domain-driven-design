import pytest


@pytest.fixture
async def order_repository(pgsql):
    class Context:
        def __init__(self):
            pass

        @staticmethod
        def get_orders():
            cursor = pgsql['20240526213109_init'].cursor()
            try:
                cursor.execute('SELECT * FROM delivery.orders')
                return cursor.fetchall()
            finally:
                cursor.close()

    return Context()
