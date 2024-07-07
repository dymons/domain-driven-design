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
                    INSERT INTO 
                        delivery.couriers 
                        (
                             id, 
                             name, 
                             status, 
                             transport, 
                             current_location
                        )
                    VALUES 
                        {rows}
                """)
            finally:
                cursor.close()

        @staticmethod
        def __to_record(courier):
            return (
                courier['id'],
                courier['name'],
                courier['status'],
                f'('
                f'  {courier["transport"]["id"]},'
                f'  "{courier["transport"]["name"]}",'
                f'  {courier["transport"]["speed"]},'
                f'  {courier["transport"]["capacity"]}'
                f')',
                f'('
                f'  {courier["current_location"]["x"]},'
                f'  {courier["current_location"]["y"]}'
                f')',
            )

    return Context()
