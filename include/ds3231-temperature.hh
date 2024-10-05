// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "common.hh"

namespace DS3231
{
	template <I2cConcept T>
	class Temperature
	{
	public:
		Temperature(T* i2c)
			: i2c(i2c), registers{}
		{
		}

		int8_t degrees()
		{
			return registers[0];
		}

		int64_t microdegrees()
		{
			uint8_t quarters = extract_bits<6, 2>(registers[1]);
			return degrees() * 1000000 + quarters * 250000;
		}

		bool retrieve()
		{
			const uint8_t address = 0x11;
			i2c->blocking_write(0x68, &address, sizeof(address), true);
			return i2c->blocking_read(0x68, registers, sizeof(registers));
		}

	private:
		T* i2c;
		uint8_t registers[2];
	};
}
