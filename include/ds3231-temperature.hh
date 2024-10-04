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

		int8_t whole()
		{
			return static_cast<int8_t>(extract_bits<0, 8>(registers[0]));
		}

		uint8_t quarters()
		{
			return extract_bits<6, 2>(registers[1]);
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
