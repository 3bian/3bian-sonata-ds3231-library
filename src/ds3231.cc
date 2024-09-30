// Copyright 3bian Limited.
// SPDX-License-Identifier: Apache-2.0

#include "ds3231.hh"

namespace DS3231
{
    bool read_datetime(volatile OpenTitanI2c* i2c, DateTime* datetime)
    {
        i2c->blocking_write(I2C_ADDRESS, &REG_DATETIME, sizeof(REG_DATETIME), true);

        auto* read_buffer = reinterpret_cast<uint8_t*>(datetime);
        return i2c->blocking_read(I2C_ADDRESS, read_buffer, sizeof(DateTime));
    }

    bool read_temperature(volatile OpenTitanI2c* i2c, Temperature* temperature)
    {
        i2c->blocking_write(I2C_ADDRESS, &REG_TEMPERATURE, sizeof(REG_TEMPERATURE), true);

        auto* read_buffer = reinterpret_cast<uint8_t*>(temperature);
        return i2c->blocking_read(I2C_ADDRESS, read_buffer, sizeof(Temperature));
    }
}
