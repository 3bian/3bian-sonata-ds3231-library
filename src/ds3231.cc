// Copyright 3bian Limited.
// SPDX-License-Identifier: Apache-2.0

#include "ds3231.hh"

namespace DS3231
{
    bool read_control(volatile OpenTitanI2c* i2c, Control& control)
    {
        i2c->blocking_write(I2CAddress, &ControlRegisterAddress, sizeof(ControlRegisterAddress), true);

        auto* readBuffer = reinterpret_cast<uint8_t*>(&control);
        return i2c->blocking_read(I2CAddress, readBuffer, sizeof(Control));
    }

    bool read_datetime(volatile OpenTitanI2c* i2c, DateTime& datetime)
    {
        i2c->blocking_write(I2CAddress, &DateTimeRegisterAddress, sizeof(DateTimeRegisterAddress), true);

        auto* readBuffer = reinterpret_cast<uint8_t*>(&datetime);
        return i2c->blocking_read(I2CAddress, readBuffer, sizeof(DateTime));
    }

    bool read_temperature(volatile OpenTitanI2c* i2c, Temperature& temperature)
    {
        i2c->blocking_write(I2CAddress, &TemperatureRegisterAddress, sizeof(TemperatureRegisterAddress), true);

        auto* readBuffer = reinterpret_cast<uint8_t*>(&temperature);
        return i2c->blocking_read(I2CAddress, readBuffer, sizeof(Temperature));
    }

    void write_control(volatile OpenTitanI2c* i2c, const Control& control)
    {
        RegisterPayload<Control> payload(ControlRegisterAddress, control);

        auto* writeBuffer = reinterpret_cast<uint8_t*>(&payload);
        i2c->blocking_write(I2CAddress, writeBuffer, sizeof(RegisterPayload<Control>), true);
    }

    void write_datetime(volatile OpenTitanI2c* i2c, const DateTime& datetime)
    {
        RegisterPayload<DateTime> payload(DateTimeRegisterAddress, datetime);

        auto* writeBuffer = reinterpret_cast<uint8_t*>(&payload);
        i2c->blocking_write(I2CAddress, writeBuffer, sizeof(RegisterPayload<DateTime>), true);
    }
}