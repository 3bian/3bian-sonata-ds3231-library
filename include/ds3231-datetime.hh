// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <ds3231-common.hh>

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

	template <I2c T>
	class DateTime
	{
	public:
		DateTime(volatile T* i2c);

		uint8_t seconds();
		void set_seconds(uint8_t seconds);

		uint8_t minutes();
		void set_minutes(uint8_t minutes);

		uint8_t hours();
		void set_hours(uint8_t hours);

		bool is_international_time();
		void set_international_time(bool enable);

		Meridian meridian();
		void set_meridian(Meridian meridian);

		Weekday weekday();
		void set_weekday(Weekday weekday);

		uint8_t day();
		void set_day(uint8_t day);

		bool century();
		void set_century(bool century);

		uint8_t month();
		void set_month(uint8_t month);

		uint8_t year();
		void set_year(uint8_t year);

		bool retrieve();
		void store();

	private:
		volatile T* i2c;
		uint8_t registers[7];
	};

	template <I2c T>
	DateTime<T>::DateTime(volatile T* i2c)
		: i2c(i2c), registers{}
	{
	}

	template <I2c T>
	uint8_t DateTime<T>::seconds()
	{
		return extract_bcd_bits(registers, 0x00, 0x0, 0x4, 0x4, 0x3);
	}

	template <I2c T>
	void DateTime<T>::set_seconds(uint8_t seconds)
	{
		assign_bcd_bits(registers, 0x00, seconds, 0x0, 0x4, 0x4, 0x3);
	}

	template <I2c T>
	uint8_t DateTime<T>::minutes()
	{
		return extract_bcd_bits(registers, 0x01, 0x0, 0x4, 0x4, 0x3);
	}

	template <I2c T>
	void DateTime<T>::set_minutes(uint8_t minutes)
	{
		assign_bcd_bits(registers, 0x01, minutes, 0x0, 0x4, 0x4, 0x3);
	}

	template <I2c T>
	uint8_t DateTime<T>::hours()
	{
		if (is_international_time())
		{
			return extract_bcd_bits(registers, 0x02, 0x0, 0x4, 0x4, 0x2);
		}

		return extract_bcd_bits(registers, 0x02, 0x0, 0x4, 0x4, 0x1);
	}

	template <I2c T>
	void DateTime<T>::set_hours(uint8_t hours)
	{
		assign_bcd_bits(registers, 0x02, hours, 0x0, 0x4, 0x4, 0x2);
	}

	template <I2c T>
	bool DateTime<T>::is_international_time()
	{
		return extract_bits(registers, 0x02, 0x6, 0x1);
	}

	template <I2c T>
	void DateTime<T>::set_international_time(bool enable)
	{
		assign_bits(registers, 0x02, 0x6, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	Meridian DateTime<T>::meridian()
	{
		if (!is_international_time())
		{
			return static_cast<Meridian>(extract_bits(registers, 0x02, 0x5, 0x1));
		}

		if (hours() < 12)
		{
			return Meridian::AM;
		}

		return Meridian::PM;
	}

	template <I2c T>
	void DateTime<T>::set_meridian(Meridian meridian)
	{
		assign_bits(registers, 0x02, 0x5, 0x1, static_cast<uint8_t>(meridian));
	}

	template <I2c T>
	Weekday DateTime<T>::weekday()
	{
		return static_cast<Weekday>(extract_bits(registers, 0x03, 0x0, 0x2));
	}

	template <I2c T>
	void DateTime<T>::set_weekday(Weekday weekday)
	{
		assign_bits(registers, 0x03, 0x0, 0x2, static_cast<uint8_t>(weekday));
	}

	template <I2c T>
	uint8_t DateTime<T>::day()
	{
		return extract_bcd_bits(registers, 0x04, 0x0, 0x4, 0x4, 0x2);
	}

	template <I2c T>
	void DateTime<T>::set_day(uint8_t day)
	{
		assign_bcd_bits(registers, 0x04, day, 0x0, 0x4, 0x4, 0x2);
	}

	template <I2c T>
	bool DateTime<T>::century()
	{
		return extract_bits(registers, 0x05, 0x7, 0x1);
	}

	template <I2c T>
	void DateTime<T>::set_century(bool century)
	{
		assign_bits(registers, 0x05, 0x7, 0x1, century ? 1 : 0);
	}

	template <I2c T>
	uint8_t DateTime<T>::month()
	{
		return extract_bcd_bits(registers, 0x05, 0x0, 0x4, 0x4, 0x2);
	}

	template <I2c T>
	void DateTime<T>::set_month(uint8_t month)
	{
		assign_bcd_bits(registers, 0x05, month, 0x0, 0x4, 0x4, 0x2);
	}

	template <I2c T>
	uint8_t DateTime<T>::year()
	{
		return extract_bcd_bits(registers, 0x06, 0x0, 0x4, 0x4, 0x4);
	}

	template <I2c T>
	void DateTime<T>::set_year(uint8_t year)
	{
		assign_bcd_bits(registers, 0x06, year, 0x0, 0x4, 0x4, 0x4);
	}

	template <I2c T>
	bool DateTime<T>::retrieve()
	{
		static const uint8_t address = 0x00;

		i2c->blocking_write(0x68, &address, sizeof(address), true);
		return i2c->blocking_read(0x68, registers, sizeof(registers));
	}

	template <I2c T>
	void DateTime<T>::store()
	{
		static const uint8_t address = 0x00;

		uint8_t writeBuffer[sizeof(registers) + 1];
		writeBuffer[0] = address;
		writeBuffer[1] = registers[0];
		writeBuffer[2] = registers[1];
		writeBuffer[3] = registers[2];
		writeBuffer[4] = registers[3];
		writeBuffer[5] = registers[4];
		writeBuffer[6] = registers[5];
		writeBuffer[7] = registers[6];
		i2c->blocking_write(0x68, writeBuffer, sizeof(writeBuffer), true);
	}
}