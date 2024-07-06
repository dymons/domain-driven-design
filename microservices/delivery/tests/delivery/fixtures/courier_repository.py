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
            current_location: Location = Location(x=1, y=1),
    ):
        self.id = id
        self.name = name
        self.status = status
        self.transport = transport
        self.current_location = current_location

    def to_record(self):
        return (
            self.id,
            self.name,
            self.status.name,
            f'({self.transport.id}, "{self.transport.name}", {self.transport.speed}, {self.transport.capacity})',
            f'({self.current_location.x},{self.current_location.y})',
        )


@pytest.fixture
async def courier_repository(pgsql):
    class Context:
        def __init__(self):
            self._db = '20240526213109_init'

        def insert_couriers(self, couriers: List[Courier]):
            if not couriers:
                return

            rows = ",".join(map(str, [c.to_record() for c in couriers]))
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

    return Context()
