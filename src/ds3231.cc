// Copyright 3bian Limited.
// SPDX-License-Identifier: Apache-2.0

#include "ds3231.hh"

namespace DS3231
{
	Control::Control()
	{
	}

	bool Control::get_alarm1_interrupt_enable() const
	{
		return extract_bits(registers, 0x00, 0x0, 0x1);
	}

	void Control::set_alarm1_interrupt_enable(bool enable)
	{
		assign_bits(registers, 0x00, 0x0, 0x1, enable ? 1 : 0);
	}

	bool Control::get_alarm2_interrupt_enable() const
	{
		return extract_bits(registers, 0x00, 0x1, 0x1);
	}

	void Control::set_alarm2_interrupt_enable(bool enable)
	{
		assign_bits(registers, 0x00, 0x1, 0x1, enable ? 1 : 0);
	}

	bool Control::get_interrupt_control() const
	{
		return extract_bits(registers, 0x00, 0x2, 0x1);
	}

	void Control::set_interrupt_control(bool enable)
	{
		assign_bits(registers, 0x00, 0x2, 0x1, enable ? 1 : 0);
	}

	bool Control::get_rate_select1() const
	{
		return extract_bits(registers, 0x00, 0x3, 0x1);
	}

	void Control::set_rate_select1(bool enable)
	{
		assign_bits(registers, 0x00, 0x3, 0x1, enable ? 1 : 0);
	}

	bool Control::get_rate_select2() const
	{
		return extract_bits(registers, 0x00, 0x4, 0x1);
	}

	void Control::set_rate_select2(bool enable)
	{
		assign_bits(registers, 0x00, 0x4, 0x1, enable ? 1 : 0);
	}

	bool Control::get_convert_temperature() const
	{
		return extract_bits(registers, 0x00, 0x5, 0x1);
	}

	void Control::set_convert_temperature(bool enable)
	{
		assign_bits(registers, 0x00, 0x5, 0x1, enable ? 1 : 0);
	}

	bool Control::get_battery_backed_square_wave_enable() const
	{
		return extract_bits(registers, 0x00, 0x6, 0x1);
	}

	void Control::set_battery_backed_square_wave_enable(bool enable)
	{
		assign_bits(registers, 0x00, 0x6, 0x1, enable ? 1 : 0);
	}

	bool Control::get_disable_oscillator() const
	{
		return extract_bits(registers, 0x00, 0x7, 0x1);
	}

	void Control::set_disable_oscillator(bool enable)
	{
		assign_bits(registers, 0x00, 0x7, 0x1, enable ? 1 : 0);
	}

	const std::array<uint8_t, 1>& Control::get_registers() const
	{
		return registers;
	}

	DateTime::DateTime() : registers{0}
	{
	}

	uint8_t DateTime::get_seconds() const
	{
		return extract_bcd_bits(registers, 0x00, 0x0, 0x4, 0x4, 0x3);
	}

	void DateTime::set_seconds(uint8_t seconds)
	{
		assign_bcd_bits(registers, 0x00, seconds, 0x0, 0x4, 0x4, 0x3);
	}

	uint8_t DateTime::get_minutes() const
	{
		return extract_bcd_bits(registers, 0x01, 0x0, 0x4, 0x4, 0x3);
	}

	void DateTime::set_minutes(uint8_t minutes)
	{
		assign_bcd_bits(registers, 0x01, minutes, 0x0, 0x4, 0x4, 0x3);
	}

	uint8_t DateTime::get_hours() const
	{
		return extract_bcd_bits(registers, 0x02, 0x0, 0x4, 0x4, 0x2);
	}

	void DateTime::set_hours(uint8_t hours)
	{
		assign_bcd_bits(registers, 0x02, hours, 0x0, 0x4, 0x4, 0x2);
	}

	bool DateTime::is_international_time() const
	{
		return extract_bits(registers, 0x02, 0x6, 0x1);
	}

	void DateTime::set_international_time(bool enable)
	{
		assign_bits(registers, 0x02, 0x6, 0x1, enable ? 1 : 0);
	}

	Meridian DateTime::get_meridian() const
	{
		return static_cast<Meridian>(extract_bits(registers, 0x02, 0x5, 0x1));
	}

	void DateTime::set_meridian(Meridian meridian)
	{
		assign_bits(registers, 0x02, 0x5, 0x1, static_cast<uint8_t>(meridian));
	}

	Weekday DateTime::get_weekday() const
	{
		return static_cast<Weekday>(extract_bits(registers, 0x03, 0x0, 0x2));
	}

	void DateTime::set_weekday(Weekday weekday)
	{
		assign_bits(registers, 0x03, 0x0, 0x2, static_cast<uint8_t>(weekday));
	}

	uint8_t DateTime::get_day() const
	{
		return extract_bcd_bits(registers, 0x04, 0x0, 0x4, 0x4, 0x2);
	}

	void DateTime::set_day(uint8_t day)
	{
		assign_bcd_bits(registers, 0x04, day, 0x0, 0x4, 0x4, 0x2);
	}

	bool DateTime::get_century() const
	{
		return extract_bits(registers, 0x05, 0x7, 0x1);
	}

	void DateTime::set_century(bool century)
	{
		assign_bits(registers, 0x05, 0x7, 0x1, century ? 1 : 0);
	}

	uint8_t DateTime::get_month() const
	{
		return extract_bcd_bits(registers, 0x05, 0x0, 0x4, 0x4, 0x2);
	}

	void DateTime::set_month(uint8_t month)
	{
		assign_bcd_bits(registers, 0x05, month, 0x0, 0x4, 0x4, 0x2);
	}

	uint8_t DateTime::get_year() const
	{
		return extract_bcd_bits(registers, 0x06, 0x0, 0x4, 0x4, 0x4);
	}

	void DateTime::set_year(uint8_t year)
	{
		assign_bcd_bits(registers, 0x06, year, 0x0, 0x4, 0x4, 0x4);
	}

	const std::array<uint8_t, 7>& DateTime::get_registers() const
	{
		return registers;
	}

	Temperature::Temperature() : registers{0}
	{
	}

	int8_t Temperature::get_degrees() const
	{
		return static_cast<int8_t>(extract_bits(registers, 0x00, 0x0, 0x8));
	}

	uint8_t Temperature::get_quarters() const
	{
		return extract_bits(registers, 0x01, 0x6, 0x2);
	}

	const std::array<uint8_t, 2>& Temperature::get_registers() const
	{
		return registers;
	}
}
