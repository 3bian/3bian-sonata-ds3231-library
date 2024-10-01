// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <array>
#include <platform-i2c.hh>

namespace DS3231
{
	enum class Meridian : uint8_t
	{
		AM = 0,
		PM = 1
	};

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

	class Control
	{
	public:
		Control();

		bool get_alarm1_interrupt_enable() const;
		void set_alarm1_interrupt_enable(bool enable);

		bool get_alarm2_interrupt_enable() const;
		void set_alarm2_interrupt_enable(bool enable);

		bool get_interrupt_control() const;
		void set_interrupt_control(bool enable);

		bool get_rate_select1() const;
		void set_rate_select1(bool enable);

		bool get_rate_select2() const;
		void set_rate_select2(bool enable);

		bool get_convert_temperature() const;
		void set_convert_temperature(bool enable);

		bool get_battery_backed_square_wave_enable() const;
		void set_battery_backed_square_wave_enable(bool enable);

		bool get_disable_oscillator() const;
		void set_disable_oscillator(bool enable);

		const std::array<uint8_t, 1>& get_registers() const;

	private:
		std::array<uint8_t, 1> registers;
	};

	class DateTime
	{
	public:
		DateTime();

		uint8_t get_seconds() const;
		void set_seconds(uint8_t seconds);

		uint8_t get_minutes() const;
		void set_minutes(uint8_t minutes);

		uint8_t get_hours() const;
		void set_hours(uint8_t hours);

		bool is_international_time() const;
		void set_international_time(bool enable);

		Meridian get_meridian() const;
		void set_meridian(Meridian meridian);

		Weekday get_weekday() const;
		void set_weekday(Weekday weekday);

		uint8_t get_day() const;
		void set_day(uint8_t day);

		bool get_century() const;
		void set_century(bool century);

		uint8_t get_month() const;
		void set_month(uint8_t month);

		uint8_t get_year() const;
		void set_year(uint8_t year);

		const std::array<uint8_t, 7>& get_registers() const;

	private:
		std::array<uint8_t, 7> registers;
	};

	class Temperature
	{
	public:
		Temperature();

		int8_t get_degrees() const;
		uint8_t get_quarters() const;

		const std::array<uint8_t, 2>& get_registers() const;

	private:
		std::array<uint8_t, 2> registers;
	};

	template <typename T>
	struct RegisterPayload
	{
		uint8_t registerAddress;
		T payload;

		RegisterPayload(uint8_t registerAddress, const T& payload)
			: registerAddress(registerAddress), payload(payload)
		{
		}
	};

	bool read_control(volatile OpenTitanI2c* i2c, Control& control);
	bool read_datetime(volatile OpenTitanI2c* i2c, DateTime& datetime);
	bool read_temperature(volatile OpenTitanI2c* i2c, Temperature& temperature);
	void write_control(volatile OpenTitanI2c* i2c, const Control& control);
	void write_datetime(volatile OpenTitanI2c* i2c, const DateTime& datetime);

	template <size_t N>
	inline void assign_bits(std::array<uint8_t, N>& buffer, uint8_t index,
		uint8_t offset, uint8_t count, uint8_t value)
	{
		uint8_t mask = ((1u << count) - 1u) << offset;
		buffer[index] = (buffer[index] & ~mask) | ((value << offset) & mask);
	}

	template <size_t N>
	inline void assign_bcd_bits(std::array<uint8_t, N>& buffer, uint8_t index,
		uint8_t value, uint8_t unitsOffset, uint8_t tensOffset,
		uint8_t unitsBits, uint8_t tensBits)
	{
		uint8_t units = value % 10u;
		uint8_t tens  = value / 10u;
		assign_bits(buffer, index, unitsOffset, unitsBits, units);
		assign_bits(buffer, index, tensOffset, tensBits, tens);
	}

	template <size_t N>
	inline uint8_t extract_bits(const std::array<uint8_t, N>& buffer,
		uint8_t index, uint8_t offset, uint8_t count)
	{
		return (buffer[index] >> offset) & ((1u << count) - 1u);
	}

	template <size_t N>
	inline uint8_t extract_bcd_bits(const std::array<uint8_t, N>& buffer,
		uint8_t index, uint8_t unitsOffset, uint8_t tensOffset,
		uint8_t unitsBits, uint8_t tensBits)
	{
		uint8_t units = extract_bits(buffer, index, unitsOffset, unitsBits);
		uint8_t tens  = extract_bits(buffer, index, tensOffset, tensBits);
		return static_cast<uint8_t>(10u * tens + units);
	}
}
