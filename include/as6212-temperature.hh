// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "common.hh"

namespace AS6212
{
	template <I2cConcept T>
	class Temperature
	{
	public:
		Temperature(T* i2c)
			: i2c(i2c), registers{}
		{
		}

		int16_t whole()
		{
			uint8_t msb = registers[0];
			uint8_t lsb = extract_bits<7, 1>(registers[1]);
			return (msb << 1) | lsb;
		}

		uint8_t fraction()
		{
			return extract_bits<0, 7>(registers[1]);
		}

		bool retrieve()
		{
			const uint8_t address = 0x00;
			i2c->blocking_write(0x48, &address, sizeof(address), true);
			return i2c->blocking_read(0x48, registers, sizeof(registers));
		}

	private:
		T* i2c;
		uint8_t registers[2];
	};
}