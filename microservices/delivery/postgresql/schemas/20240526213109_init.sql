-- +goose Up
-- +goose StatementBegin
CREATE SCHEMA IF NOT EXISTS delivery;

DROP TYPE IF EXISTS delivery.transport;
CREATE TYPE delivery.transport AS
(
    id       INTEGER,
    name     TEXT,
    speed    INTEGER,
    capacity INTEGER
);

DROP TYPE IF EXISTS delivery.location;
CREATE TYPE delivery.location AS
(
    x INTEGER,
    y INTEGER
);

DROP TYPE IF EXISTS delivery.weight;
CREATE TYPE delivery.weight AS
(
    value INTEGER
);

DROP TYPE IF EXISTS delivery.order;
CREATE TYPE delivery.order AS
(
    id         TEXT,
    status     TEXT,
    courier_id TEXT
);

CREATE TABLE IF NOT EXISTS delivery.orders
(
    id                TEXT              NOT NULL,
    status            TEXT              NOT NULL,
    courier_id        TEXT,
    delivery_location delivery.location NOT NULL,
    weight            delivery.weight   NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS delivery.couriers
(
    id               TEXT               NOT NULL,
    name             TEXT               NOT NULL,
    status           TEXT               NOT NULL,
    transport        delivery.transport NOT NULL,
    current_location delivery.location  NOT NULL,

    PRIMARY KEY (id)
);

CREATE INDEX IF NOT EXISTS idx_orders_status ON delivery.orders USING btree (status);
CREATE INDEX IF NOT EXISTS idx_couriers_status ON delivery.couriers USING btree (status);
-- +goose StatementEnd

-- +goose Down
-- +goose StatementBegin
-- +goose StatementEnd
