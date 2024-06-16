async def test_basic(service_client):
    response = await service_client.post('/api/v1/orders',
                                         json={
                                             'basket_id': 'basket_id1',
                                             'address': 'address',
                                             'weight': 1
                                         })
    assert response.status == 200
