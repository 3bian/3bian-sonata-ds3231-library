// Copyright 3bian Limited.
// SPDX-License-Identifier: Apache-2.0

#include "ds3231.hh"

namespace DS3231
{
    bool read_control(volatile OpenTitanI2c* i2c, Control& control)
    {
        i2c->blocking_write(I2C_ADDRESS, &REG_CONTROL, sizeof(REG_CONTROL), true);

        auto* read_buffer = reinterpret_cast<uint8_t*>(&control);
        return i2c->blocking_read(I2C_ADDRESS, read_buffer, sizeof(Control));
    }

    bool read_datetime(volatile OpenTitanI2c* i2c, DateTime& datetime)
    {
        i2c->blocking_write(I2C_ADDRESS, &REG_DATETIME, sizeof(REG_DATETIME), true);

        auto* read_buffer = reinterpret_cast<uint8_t*>(&datetime);
        return i2c->blocking_read(I2C_ADDRESS, read_buffer, sizeof(DateTime));
    }

    bool read_temperature(volatile OpenTitanI2c* i2c, Temperature& temperature)
    {
        i2c->blocking_write(I2C_ADDRESS, &REG_TEMPERATURE, sizeof(REG_TEMPERATURE), true);

        auto* read_buffer = reinterpret_cast<uint8_t*>(&temperature);
        return i2c->blocking_read(I2C_ADDRESS, read_buffer, sizeof(Temperature));
    }

    void write_control(volatile OpenTitanI2c* i2c, const Control& control)
    {
        RegisterPayload<Control> payload(REG_CONTROL, control);

        auto* write_buffer = reinterpret_cast<uint8_t*>(&payload);
        i2c->blocking_write(I2C_ADDRESS, write_buffer, sizeof(RegisterPayload<Control>), true);
    }

    void write_datetime(volatile OpenTitanI2c* i2c, const DateTime& datetime)
    {
        RegisterPayload<DateTime> payload(REG_DATETIME, datetime);

        auto* write_buffer = reinterpret_cast<uint8_t*>(&payload);
        i2c->blocking_write(I2C_ADDRESS, write_buffer, sizeof(RegisterPayload<DateTime>), true);
    }
}