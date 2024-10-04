// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "common.hh"

namespace DS1307
{
	template <I2cConcept T>
	class DateTime
	{
	public:
		DateTime(T* i2c)
			: i2c(i2c), registers{}
		{
		}

		uint8_t seconds()
		{
			uint8_t units = extract_bits<0, 4>(registers[0]);
			uint8_t tens  = extract_bits<4, 3>(registers[0]);
			return 10 * tens + units;
		}

		void set_seconds(uint8_t value)
		{
			uint8_t units = value % 10;
			uint8_t tens  = value / 10;
			assign_bits<0, 4>(&registers[0], units);
			assign_bits<4, 3>(&registers[0], tens);
		}

		uint8_t minutes()
		{
			uint8_t units = extract_bits<0, 4>(registers[1]);
			uint8_t tens  = extract_bits<4, 3>(registers[1]);
			return 10 * tens + units;
		}

		void set_minutes(uint8_t value)
		{
			uint8_t units = value % 10;
			uint8_t tens  = value / 10;
			assign_bits<0, 4>(&registers[1], units);
			assign_bits<4, 3>(&registers[1], tens);
		}

		uint8_t hours()
		{
			uint8_t units = extract_bits<0, 4>(registers[2]);
			uint8_t tens;
			if (is_24_hour_time())
			{
				tens = extract_bits<4, 2>(registers[2]);
			}
			else
			{
				tens = extract_bits<4, 1>(registers[2]);
			}
			return 10 * tens + units;
		}

		void set_hours(uint8_t value)
		{
			uint8_t units = value % 10;
			uint8_t tens  = value / 10;
			assign_bits<0, 4>(&registers[2], units);
			assign_bits<4, 2>(&registers[2], tens);
		}

		bool is_24_hour_time()
		{
			return extract_bits<6, 1>(registers[2]);
		}

		void set_is_24_hour_time(bool value)
		{
			assign_bits<6, 1>(&registers[2], value);
		}

		bool is_pm()
		{
			if (!is_24_hour_time())
			{
				return extract_bits<5, 1>(registers[2]);
			}
			else if (hours() < 12)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		void set_is_pm(bool value)
		{
			assign_bits<5, 1>(&registers[2], value);
		}

		uint8_t weekday()
		{
			return extract_bits<0, 3>(registers[3]);
		}

		void set_weekday(bool value)
		{
			assign_bits<0, 3>(&registers[3], value);
		}

		uint8_t day()
		{
			uint8_t units = extract_bits<0, 4>(registers[4]);
			uint8_t tens  = extract_bits<4, 2>(registers[4]);
			return 10 * tens + units;
		}

		void set_day(uint8_t value)
		{
			uint8_t units = value % 10;
			uint8_t tens  = value / 10;
			assign_bits<0, 4>(&registers[4], units);
			assign_bits<4, 2>(&registers[4], tens);
		}

		uint8_t month()
		{
			uint8_t units = extract_bits<0, 4>(registers[5]);
			uint8_t tens  = extract_bits<4, 2>(registers[5]);
			return 10 * tens + units;
		}

		void set_month(uint8_t value)
		{
			uint8_t units = value % 10;
			uint8_t tens  = value / 10;
			assign_bits<0, 4>(&registers[5], units);
			assign_bits<4, 2>(&registers[5], tens);
		}

		uint8_t year()
		{
			uint8_t units = extract_bits<0, 4>(registers[6]);
			uint8_t tens  = extract_bits<4, 4>(registers[6]);
			return 10 * tens + units;
		}

		void set_year(uint8_t value)
		{
			uint8_t units = value % 10;
			uint8_t tens  = value / 10;
			assign_bits<0, 4>(&registers[6], units);
			assign_bits<4, 4>(&registers[6], tens);
		}

		bool retrieve()
		{
			const uint8_t address = 0x00;

			i2c->blocking_write(0x68, &address, sizeof(address), true);
			return i2c->blocking_read(0x68, registers, sizeof(registers));
		}

		void store()
		{
			uint8_t buffer[sizeof(registers) + 1] = { 0x00 };
			std::copy(std::begin(registers), std::end(registers), &buffer[1]);

			i2c->blocking_write(0x68, buffer, sizeof(buffer), true);
		}

	private:
		T* i2c;
		uint8_t registers[7];
	};
}
