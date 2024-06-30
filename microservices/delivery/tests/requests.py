
def fake_basket_id() -> str:
    return 'fake_basket_id'


def get_api_v1_orders_request():
    return {
        'basket_id': fake_basket_id(),
        'address': 'address',
        'weight': 1,
    }
