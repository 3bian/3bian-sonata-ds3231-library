// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "common.hh"

namespace DS1307
{
	template <I2cConcept T>
	class Control
	{
	public:
		Control(T* i2c)
			: i2c(i2c), registers{}
		{
		}

		bool rate_select0()
		{
			return extract_bits<0, 1>(registers[0]);
		}

		void set_rate_select0(bool value)
		{
			assign_bits<0, 1>(&registers[0], value);
		}

		bool rate_select1()
		{
			return extract_bits<1, 1>(registers[0]);
		}

		void set_rate_select1(bool value)
		{
			assign_bits<1, 1>(&registers[0], value);
		}

		bool battery_backed_square_wave_enable()
		{
			return extract_bits<4, 1>(registers[0]);
		}

		void set_battery_backed_square_wave_enable(bool value)
		{
			assign_bits<4, 1>(&registers[0], value);
		}

		bool disable_oscillator()
		{
			return extract_bits<7, 1>(registers[0]);
		}

		void set_disable_oscillator(bool value)
		{
			assign_bits<7, 1>(&registers[0], value);
		}

		bool retrieve()
		{
			const uint8_t address = 0x0e;

			i2c->blocking_write(0x68, &address, sizeof(address), true);
			return i2c->blocking_read(0x68, registers, sizeof(registers));
		}

		void store()
		{
			uint8_t buffer[sizeof(registers) + 1] = { 0x0e };
			std::copy(std::begin(registers), std::end(registers), &buffer[1]);

			i2c->blocking_write(0x68, buffer, sizeof(buffer), true);
		}

	private:
		T* i2c;
		uint8_t registers[1];
	};
}
