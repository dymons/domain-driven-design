import pytest


@pytest.fixture
async def courier_repository(pgsql):
    class Context:
        def __init__(self):
            pass

        # noinspection PyMethodMayBeStatic
        def get_couriers(self):
            cursor = pgsql['20240526213109_init'].cursor()
            try:
                cursor.execute('SELECT * FROM delivery.couriers')
                return cursor.fetchall()
            finally:
                cursor.close()

    return Context()
