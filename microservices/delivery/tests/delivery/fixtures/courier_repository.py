import pytest

from typing import List
from typing import Dict
from typing import Any


@pytest.fixture
async def courier_repository(pgsql):
    class Context:
        def __init__(self):
            self._db = '20240526213109_init'

        def insert_couriers(self, couriers: List[Dict[str, Any]]):
            if not couriers:
                return

            rows = ",".join(map(str, [self.__to_record(c) for c in couriers]))
            cursor = pgsql[self._db].cursor()

            try:
                cursor.execute(f"""
                    INSERT INTO delivery.couriers 
                    (
                         id, 
                         name, 
                         status, 
                         transport, 
                         current_location
                     ) 
                    VALUES {rows}
                """)
            finally:
                cursor.close()

        def __to_record(self, courier):
            return (
                courier['id'],
                courier['name'],
                courier['status'],
                f'({courier["transport"]["id"]}, "{courier["transport"]["name"]}", {courier["transport"]["speed"]}, {courier["transport"]["capacity"]})',
                f'({courier["current_location"]["x"]},{courier["current_location"]["y"]})',
            )

    return Context()
