import pytest

from microservices.delivery.tests.delivery.utils.types import default_basket_id
from microservices.delivery.tests.delivery.fixtures.order_repository import order_repository
from microservices.delivery.tests.delivery.fixtures.api_v1_orders import api_v1_orders
from microservices.delivery.tests.delivery.fixtures.api_v1_orders import default_api_v1_orders_request


@pytest.mark.parametrize(
    'api_v1_orders_request, api_v1_orders_expected_response',
    [
        (
            default_api_v1_orders_request(basket_id=''),
            {'code': '400', 'message': 'basket_id is empty'},
        ),
        (
            default_api_v1_orders_request(address=''),
            {'code': '400', 'message': 'address is empty'},
        ),
        (
            default_api_v1_orders_request(weight=-1),
            {'code': '400', 'message': 'weight should be positive'},
        ),
    ],
)
async def test_bad_request(
        api_v1_orders,
        order_repository,
        api_v1_orders_request,
        api_v1_orders_expected_response,
):
    # Arrange
    api_v1_orders.request = api_v1_orders_request

    # Act
    response = await api_v1_orders.execute()

    # Assert
    assert response.status == 400
    assert response.json() == api_v1_orders_expected_response


async def test_given_empty_orders_when_create_order_then_order_is_created(
        api_v1_orders,
        order_repository,
):
    # Arrange & Act
    response = await api_v1_orders.execute()

    # Assert
    assert response.status == 200
    assert order_repository.get_orders() == [
        (default_basket_id(), 'created', None, '(1,1)', '(1)'),
    ]


async def test_given_empty_orders_when_create_same_order_several_times_then_order_is_created_once(
        api_v1_orders,
        order_repository,
):
    # Arrange & Act
    response_first = await api_v1_orders.execute()
    response_second = await api_v1_orders.execute()

    # Assert
    assert response_first.status == 200
    assert response_second.status == 200
    assert order_repository.get_orders() == [
        (default_basket_id(), 'created', None, '(1,1)', '(1)'),
    ]
