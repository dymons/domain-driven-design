from typing import NewType
from typing import Dict
from typing import Any
from enum import Enum


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
        transport: Dict[str, Any] = Defaults.transport,
        current_location: Dict[str, Any] = Defaults.delivery_location,
):
    return {
        'id': id,
        'name': name,
        'status': status,
        'transport': transport,
        'current_location': current_location,
    }

BasketId = NewType('basket_id', str)
CourierId = NewType('courier_id', str)
CourierName = NewType('courier_name', str)
CourierStatus = Enum('courier_status', ['not_available', 'ready', 'busy'])


class Transport:
    def __init__(
            self,
            id: int = 1,
            name: str = 'pedestrian',
            speed: int = 1,
            capacity: int = 1,
    ):
        self.id = id
        self.name = name
        self.speed = speed
        self.capacity = capacity


class Location:
    def __init__(
            self,
            x: int = 1,
            y: int = 1,
    ):
        self.x = x
        self.y = y

    def to_json(self):
        return {'x': self.x, 'y': self.y}

    @staticmethod
    def from_record(record):
        return Location(x=record[0], y=record[1])


def default_basket_id() -> BasketId:
    return BasketId('default_basket_id')


def default_courier_id() -> CourierId:
    return CourierId('default_courier_id')


def default_courier_name() -> CourierName:
    return CourierName('default_courier_name')


def default_courier_status() -> CourierStatus:
    return CourierStatus['not_available']


def default_transport() -> Transport:
    return Transport(id=1, name='pedestrian', speed=1, capacity=1)


def default_location() -> Dict[str, Any]:
    return {'x': 1, 'y': 1}


def default_order_id() -> str:
    return 'default_order_id'
