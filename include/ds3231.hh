// Copyright 3bian Limited.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdint.h>
#include <platform-i2c.hh>

namespace DS3231
{
    /// @brief I2C address for the DS3231 RTC module.
    constexpr uint8_t I2C_ADDRESS     = 0x68;

    /// @brief Register address for the Control register in the DS3231.
    constexpr uint8_t REG_CONTROL     = 0x0E;

    /// @brief Register address for DateTime in the DS3231.
    constexpr uint8_t REG_DATETIME    = 0x00;

    /// @brief Register address for Temperature in the DS3231.
    constexpr uint8_t REG_TEMPERATURE = 0x11;

    /// @brief Enum class representing the AM/PM indicator for 12-hour mode.
    enum class Meridian : uint8_t
    {
        AM = 0,
        PM = 1
    };

    /// @brief Enum class representing days of the week for the DS3231.
    enum class Weekday : uint8_t 
    {
        Sunday    = 0,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    };

    #pragma pack(push, 1)

    /// @brief Structure representing control data stored in the DS3231.
    struct Control
    {
        bool           aral         : 1;    // Alarm 1 Interrupt Enable (bit 0)
        bool           a2ie         : 1;    // Alarm 2 Interrupt Enable (bit 1)
        bool           intcn        : 1;    // Interrupt Control (bit 2)
        bool           rs1          : 1;    // Rate Select 1 (bit 3)
        bool           rs2          : 1;    // Rate Select 2 (bit 4)
        bool           conv         : 1;    // Convert Temperature (bit 5)
        bool           bbsqw        : 1;    // Battery-Backed Square-Wave Enable (bit 6)
        bool           eosc         : 1;    // Enable Oscillator (bit 7)
    };

    /// @brief Structure representing Date and Time stored in the DS3231 registers.
    struct DateTime
    {
        uint8_t        second_units : 4;
        uint8_t        second_tens  : 3;
        uint8_t                     : 1;
        uint8_t        minute_units : 4;
        uint8_t        minute_tens  : 3;
        uint8_t                     : 1;
        uint8_t        hour_units   : 4;

        // Union to handle the differences between 12-hour and 24-hour formats.
        union
        {
            struct
            {
                uint8_t  hour_tens  : 1;
                Meridian meridian   : 1;
            } hour_12;

            struct
            {
                uint8_t hour_tens   : 2;
            } hour_24;
        };

        bool           is_24_hour   : 1;
        uint8_t                     : 1;
        Weekday        weekday      : 3;
        uint8_t                     : 5;

        uint8_t        day_units    : 4;
        uint8_t        day_tens     : 2;
        uint8_t                     : 2;

        uint8_t        month_units  : 4;
        uint8_t        month_tens   : 1;
        uint8_t                     : 2;
        uint8_t        century      : 1;

        uint8_t        year_units   : 4;
        uint8_t        year_tens    : 4;
    };

    /// @brief Structure representing Temperature data stored in the DS3231.
    struct Temperature
    {
        int8_t         degrees      : 8;    // Signed 8-bit integer for degrees.
        uint8_t        quarters     : 2;    // 2-bit fraction representing 0.25°C increments.
        uint8_t                     : 6;    // Padding to align to 1 byte.
    };

    /// @brief Structure representing a register address with an associated payload.
    /// @tparam T The type of the payload stored in the structure.
    template <typename T>
    struct RegisterPayload
    {
        uint8_t        reg;                 // Register address.
        T              payload;             // Data payload of type T.

        RegisterPayload(uint8_t reg, const T& payload)
            : reg(reg), payload(payload)
        {
        }
    };

    #pragma pack(pop)

    /// @brief Reads the Control register from the DS3231 RTC module.
    /// @param i2c Pointer to an OpenTitanI2c instance used for communication.
    /// @param control Control structure reference to store the read data.
    /// @return true if the read operation is successful, false otherwise.
    bool read_control(volatile OpenTitanI2c* i2c, Control& control);

    /// @brief Reads the DateTime from the DS3231 RTC module.
    /// @param i2c Pointer to an OpenTitanI2c instance used for communication.
    /// @param datetime DateTime structure reference to store the read data.
    /// @return true if the read operation is successful, false otherwise.
    bool read_datetime(volatile OpenTitanI2c* i2c, DateTime& datetime);

    /// @brief Reads the Temperature from the DS3231 RTC module.
    /// @param i2c Pointer to an OpenTitanI2c instance used for communication.
    /// @param temperature Temperature structure reference to store the read data.
    /// @return true if the read operation is successful, false otherwise.
    bool read_temperature(volatile OpenTitanI2c* i2c, Temperature& temperature);

    /// @brief Writes the Control register to the DS3231 RTC module.
    /// @param i2c Pointer to an OpenTitanI2c instance used for communication.
    /// @param control Control structure reference containing the data to write.
    void write_control(volatile OpenTitanI2c* i2c, const Control& control);

    /// @brief Writes the DateTime to the DS3231 RTC module.
    /// @param i2c Pointer to an OpenTitanI2c instance used for communication.
    /// @param datetime DateTime structure reference containing the data to write.
    void write_datetime(volatile OpenTitanI2c* i2c, const DateTime& datetime);
}
