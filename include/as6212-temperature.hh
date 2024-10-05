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

		int64_t microdegrees()
		{
			int16_t aggregatedValue = (registers[0] << 8) | registers[1];
			return aggregatedValue * 1000000LL / 128;
		}

		int16_t degrees()
		{
			return microdegrees() / 1000000;
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
