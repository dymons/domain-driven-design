async def test_basic(delivery_service):
    response = await delivery_service.post('/api/v1/orders',
                                           json={
                                               'basket_id': 'basket_id1',
                                               'address': 'address',
                                               'weight': 1
                                           })
    assert response.status == 200
