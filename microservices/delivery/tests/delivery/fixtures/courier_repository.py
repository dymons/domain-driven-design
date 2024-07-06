import pytest

from typing import List


@pytest.fixture
async def courier_repository(pgsql):
    class Context:
        def __init__(self):
            self.db = '20240526213109_init'

        def insert_couriers(self, couriers: List):
            rows = ",".join(map(str, couriers))
            cursor = pgsql[self.db].cursor()
            try:
                cursor.execute(f"""
                    INSERT INTO delivery.couriers (id, name, status, transport, current_location) 
                    VALUES {rows}
                """)
                return cursor.fetchall()
            finally:
                cursor.close()

        def get_couriers(self):
            cursor = pgsql[self.db].cursor()
            try:
                cursor.execute('SELECT * FROM delivery.couriers')
                return cursor.fetchall()
            finally:
                cursor.close()

    return Context()
