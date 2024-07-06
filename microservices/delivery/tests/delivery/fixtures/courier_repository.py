import pytest

from typing import List


class Courier:
    def __init__(
        self,
        id: str = 'id',
        name: str = 'name',
        status: str = 'not_available',
        transport: str = '(1, "pedestrian", 1, 1)',
        current_location: str = '(1,1)',
    ):
        self.id = id
        self.name = name
        self.status = status
        self.transport = transport
        self.current_location = current_location


@pytest.fixture
async def courier_repository(pgsql):
    class Context:
        def __init__(self):
            self._db = '20240526213109_init'

        def insert_couriers(self, couriers: List):
            if not couriers:
                return

            rows = ",".join(map(str, couriers))
            cursor = pgsql[self._db].cursor()
            try:
                cursor.execute(f"""
                    INSERT INTO delivery.couriers (id, name, status, transport, current_location) 
                    VALUES {rows}
                """)
            finally:
                cursor.close()

        def get_couriers(self):
            cursor = pgsql[self._db].cursor()
            try:
                cursor.execute('SELECT * FROM delivery.couriers')
                return cursor.fetchall()
            finally:
                cursor.close()

    return Context()
