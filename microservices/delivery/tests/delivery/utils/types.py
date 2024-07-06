from typing import NewType
from enum import Enum


BasketId = NewType('basket_id', str)
CourierId = NewType('courier_id', str)
CourierName = NewType('courier_name', str)
CourierStatus = Enum('courier_status', ['not_available', 'ready', 'busy'])


def default_basket_id() -> BasketId:
    return BasketId('default_basket_id')


def default_courier_id() -> CourierId:
    return CourierId('default_courier_id')


def default_courier_name() -> CourierName:
    return CourierName('default_courier_name')


def default_courier_status() -> CourierStatus:
    return CourierStatus('not_available')
