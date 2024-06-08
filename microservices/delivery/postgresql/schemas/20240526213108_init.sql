-- +goose Up
-- +goose StatementBegin
CREATE SCHEMA IF NOT EXISTS delivery;

CREATE TABLE IF NOT EXISTS delivery.orders
(
    id               TEXT  NOT NULL,
    name             TEXT  NOT NULL,
    transport        JSONB NOT NULL,
    current_location JSONB NOT NULL,
    status           TEXT  NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS delivery.couriers
(
    id               TEXT  NOT NULL,
    status           TEXT  NOT NULL,
    courier_id       TEXT,
    current_location JSONB NOT NULL,
    weight           INT   NOT NULL,

    PRIMARY KEY (id)
);

CREATE INDEX IF NOT EXISTS idx_orders_status ON delivery.orders USING btree (status);
CREATE INDEX IF NOT EXISTS idx_couriers_status ON delivery.couriers USING btree (status);
-- +goose StatementEnd

-- +goose Down
-- +goose StatementBegin
DROP INDEX IF EXISTS idx_couriers_status;
DROP INDEX IF EXISTS idx_orders_status;
DROP TABLE IF EXISTS delivery.couriers;
DROP TABLE IF EXISTS delivery.orders;
DROP SCHEMA IF EXISTS delivery;
-- +goose StatementEnd
