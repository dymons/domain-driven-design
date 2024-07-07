from typing import Dict
from typing import Any
from typing import Optional


class Defaults(object):
    basket_id: str = 'default_basket_id'
    courier_id: str = 'default_courier_id'
    courier_name: str = 'default_courier_name'
    courier_statis: str = 'not_available'
    order_status: str = 'created'
    delivery_location: Dict[str, Any] = {
        'x': 1,
        'y': 1,
    }
    weight: int = 1
    address: str = 'address'
    transport: Dict[str, Any] = {
        'id': 1,
        'name': 'pedestrian',
        'speed': 1,
        'capacity': 1,
    }


def make_courier(
        id: str = Defaults.courier_id,
        name: str = Defaults.courier_name,
        status: str = Defaults.courier_statis,
        transport: Optional[Dict[str, Any]] = None,
        current_location: Optional[Dict[str, Any]] = None,
):
    if current_location is None:
        current_location = Defaults.delivery_location
    if transport is None:
        transport = Defaults.transport
    return {
        'id': id,
        'name': name,
        'status': status,
        'transport': transport,
        'current_location': current_location,
    }
