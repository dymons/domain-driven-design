async def test_basic(service_client):
    response = await service_client.post('/hello', params={'name': 'Tester'})
    assert response.status == 200
    assert response.text == 'Hello, Tester!\n'
