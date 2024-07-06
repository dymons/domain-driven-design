import pytest

from ast import literal_eval as make_tuple

from typing import List
from typing import Dict
from typing import Any

from microservices.delivery.tests.delivery.utils.types import *


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
                return [
                    {
                        'id': r[0],
                        'status': r[1],
                        'courier_id': r[2] if r[2] else None,
                        'delivery_location': {
                            'x': make_tuple(r[3])[0],
                            'y': make_tuple(r[3])[1],
                        },
                        'weight': make_tuple(r[4]),
                    }
                    for r in rows]
            finally:
                cursor.close()

    return Context()
