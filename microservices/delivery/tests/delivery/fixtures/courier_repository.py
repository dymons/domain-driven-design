import pytest

from typing import List

from microservices.delivery.tests.delivery.utils.types import *


class Courier:
    def __init__(
            self,
            id: CourierId = default_courier_id(),
            name: CourierName = default_courier_name(),
            status: CourierStatus = default_courier_status(),
            transport: Transport = default_transport(),
            current_location: Location = default_location(),
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
