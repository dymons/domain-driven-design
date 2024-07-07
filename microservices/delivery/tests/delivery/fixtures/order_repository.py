import pytest

from ast import literal_eval as make_tuple

from typing import List
from typing import Dict
from typing import Any


@pytest.fixture
async def order_repository(pgsql):
    class Context:
        def __init__(self):
            self._db = '20240526213109_init'

        def get_orders(self) -> List[Dict[str, Any]]:
            cursor = pgsql[self._db].cursor()
            try:
                cursor.execute("""
                    SELECT
                        id,
                        status,
                        courier_id,
                        delivery_location,
                        weight
                    FROM 
                        delivery.orders
                """)
                rows = cursor.fetchall()
                return [self.__from_record(row) for row in rows]
            finally:
                cursor.close()

        def insert_orders(self, orders: List[Dict[str, Any]]):
            if not orders:
                return

            rows = ",".join(map(str, [self.__to_record(c) for c in orders]))
            cursor = pgsql[self._db].cursor()

            try:
                cursor.execute(f"""
                    INSERT INTO 
                        delivery.orders 
                        (
                             id, 
                             status, 
                             courier_id, 
                             delivery_location, 
                             weight
                        )
                    VALUES 
                        {rows}
                """)
            finally:
                cursor.close()

        @staticmethod
        def __to_record(order):
            return (
                order['id'],
                order['status'],
                order['courier_id'] if order['courier_id'] else f'NULL',
                f'('
                f'  {order["delivery_location"]["x"]},'
                f'  {order["delivery_location"]["y"]}'
                f')',
                f'('
                f'  {order["weight"]}'
                f')',
            )

        @staticmethod
        def __from_record(record):
            return {
                'id': record[0],
                'status': record[1],
                'courier_id': record[2] if record[2] else None,
                'delivery_location': {
                    'x': make_tuple(record[3])[0],
                    'y': make_tuple(record[3])[1],
                },
                'weight': make_tuple(record[4]),
            }

    return Context()
