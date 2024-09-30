// Copyright 3bian Limited.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdint.h>
#include <platform-i2c.hh>

namespace DS3231
{
    /// @brief I2C address for the DS3231 RTC module.
    constexpr uint8_t I2C_ADDRESS = 0x68;

    /// @brief Register address for DateTime in the DS3231.
    constexpr uint8_t REG_DATETIME = 0x00;

    /// @brief Register address for Temperature in the DS3231.
    constexpr uint8_t REG_TEMPERATURE = 0x11;

    /// @brief Enum class representing days of the week for the DS3231.
    enum class Weekday : uint8_t 
    {
        Sunday = 0,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    };

    #pragma pack(push, 1)

    /// @brief Structure representing Date and Time stored in the DS3231 registers.
    struct DateTime
    {
        uint8_t       second_units  : 4;
        uint8_t       second_tens   : 3;
        uint8_t                     : 1;
        uint8_t       minute_units  : 4;
        uint8_t       minute_tens   : 3;
        uint8_t                     : 1;
        uint8_t       hour_units    : 4;
        uint8_t       hour_tens     : 2;
        bool          is_24_hour    : 1;
        uint8_t                     : 1;
        Weekday       weekday       : 3;
        uint8_t                     : 5;
        uint8_t       day_units     : 4;
        uint8_t       day_tens      : 2;
        uint8_t                     : 2;
        uint8_t       month_units   : 4;
        uint8_t       month_tens    : 1;
        uint8_t                     : 2;
        uint8_t       century       : 1;
        uint8_t       year_units    : 4;
        uint8_t       year_tens     : 4;
    };

    /// @brief Structure representing Temperature data stored in the DS3231.
    struct Temperature
    {
        int8_t         degrees      : 8;
        uint8_t        quarters     : 2;
        uint8_t                     : 6;
    };

    #pragma pack(pop)

    /// @brief Reads the DateTime from the DS3231 RTC module.
    /// @param i2c Pointer to an OpenTitanI2c instance used for communication.
    /// @param datetime Pointer to a DateTime structure to store the read data.
    /// @return true if the read operation is successful, false otherwise.
    bool read_datetime(volatile OpenTitanI2c* i2c, DateTime* datetime);

    /// @brief Reads the Temperature from the DS3231 RTC module.
    /// @param i2c Pointer to an OpenTitanI2c instance used for communication.
    /// @param temperature Pointer to a Temperature structure to store the read data.
    /// @return true if the read operation is successful, false otherwise.
    bool read_temperature(volatile OpenTitanI2c* i2c, Temperature* temperature);
}
