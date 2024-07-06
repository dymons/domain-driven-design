from typing import NewType

BasketId = NewType('basket_id', str)
CourierId = NewType('courier_id', str)


def default_basket_id() -> BasketId:
    return BasketId('default_basket_id')


def default_courier_id() -> CourierId:
    return CourierId('default_courier_id')
