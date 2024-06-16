import pathlib
import subprocess

import pytest

from testsuite.databases.pgsql import discover

pytest_plugins = ['pytest_userver.plugins.core', 'pytest_userver.plugins.postgresql']


@pytest.fixture(scope='session')
def service_source_dir():
    """Path to root directory service."""
    return pathlib.Path(__file__).parent.parent


@pytest.fixture(scope='function')
async def delivery_service(
        service_client,
        _reset_postgres_state,
):
    await _reset_postgres_state()
    return service_client


@pytest.fixture(scope='session')
def pgsql_local(service_source_dir, pgsql_local_create):
    """Create schemas databases for tests"""
    databases = discover.find_schemas(
        'delivery',  # service name that goes to the DB connection
        [service_source_dir.joinpath('postgresql/schemas')],
    )
    return pgsql_local_create(list(databases.values()))


@pytest.fixture(scope='function')
async def _reset_postgres_state(pytestconfig, service_source_dir):
    async def __wrapper():
        # subprocess.run([
        #     "/home/dymons/go/bin/goose", "-dir", service_source_dir.joinpath('postgresql/schemas'), "postgres",
        #     'postgres://postgres:1@localhost:5432/delivery',
        #     "down",
        # ])

        subprocess.run([
            "/home/dymons/go/bin/goose", "-dir", service_source_dir.joinpath('postgresql/schemas'), "postgres",
            'postgres://postgres:1@localhost:5432/delivery',
            "up",
        ])

    return __wrapper
