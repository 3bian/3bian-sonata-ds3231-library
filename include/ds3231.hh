// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <platform-i2c.hh>

namespace DS3231
{
    constexpr uint8_t I2CAddress                  = 0x68;
    constexpr uint8_t ControlRegisterAddress      = 0x0E;
    constexpr uint8_t DateTimeRegisterAddress     = 0x00;
    constexpr uint8_t TemperatureRegisterAddress  = 0x11;

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
        bool           alarm1InterruptEnable          : 1;
        bool           alarm2InterruptEnable          : 1;
        bool           interruptControl               : 1;
        bool           rateSelect1                    : 1;
        bool           rateSelect2                    : 1;
        bool           convertTemperature             : 1;
        bool           batteryBackedSquareWaveEnable  : 1;
        bool           disableOscillator              : 1;
    };


    /// @brief Structure representing Date and Time stored in the DS3231 registers.
    struct DateTime
    {
        uint8_t        secondUnits  : 4;
        uint8_t        secondTens   : 3;
        uint8_t                     : 1;
        uint8_t        minuteUnits  : 4;
        uint8_t        minuteTens   : 3;
        uint8_t                     : 1;
        uint8_t        hourUnits    : 4;

        // Union to handle the differences between 12-hour and 24-hour formats.
        union
        {
            struct
            {
                uint8_t  hourTens   : 1;
                Meridian meridian   : 1;
            } hour12;

            struct
            {
                uint8_t hourTens    : 2;
            } hour24;
        };

        bool           is24Hour     : 1;
        uint8_t                     : 1;
        Weekday        weekday      : 3;
        uint8_t                     : 5;

        uint8_t        dayUnits     : 4;
        uint8_t        dayTens      : 2;
        uint8_t                     : 2;

        uint8_t        monthUnits   : 4;
        uint8_t        monthTens    : 1;
        uint8_t                     : 2;
        uint8_t        century      : 1;

        uint8_t        yearUnits    : 4;
        uint8_t        yearTens     : 4;
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
        uint8_t        registerAddress;     // Register address.
        T              payload;             // Data payload of type T.

        RegisterPayload(uint8_t registerAddress, const T& payload)
            : registerAddress(registerAddress), payload(payload)
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
