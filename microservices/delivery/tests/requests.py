from typing import Dict
from typing import Any


def default_basket_id() -> str:
    return 'default_basket_id'


def default_api_v1_orders_request(
        basket_id: str = default_basket_id(),
        address: str = 'address',
        weight: int = 1,
) -> Dict[str, Any]:
    return {
        'basket_id': basket_id,
        'address': address,
        'weight': weight,
    }
