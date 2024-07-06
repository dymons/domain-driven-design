from typing import NewType
from typing import Dict
from typing import Any
from enum import Enum


BasketId = NewType('basket_id', str)
CourierId = NewType('courier_id', str)
CourierName = NewType('courier_name', str)
CourierStatus = Enum('courier_status', ['not_available', 'ready', 'busy'])
OrderId = NewType('order_id', str)
OrderStatus = Enum('order_status', ['created', 'assigned', 'completed'])
Weight = NewType('weight', int)


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


def default_order_id() -> OrderId:
    return OrderId('default_order_id')


def default_order_status() -> OrderStatus:
    return OrderStatus['created']


def default_weight() -> Weight:
    return Weight(1)
