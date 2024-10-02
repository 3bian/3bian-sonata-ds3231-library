// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <ds3231-common.hh>

namespace DS3231
{
	template <I2c T>
	class Temperature
	{
	public:
		Temperature(volatile T* i2c);

		int8_t degrees();
		uint8_t quarters();

		bool retrieve();

	private:
		volatile T* i2c;
		uint8_t registers[2];
	};

	template <I2c T>
	Temperature<T>::Temperature(volatile T* i2c)
		: i2c(i2c), registers{}
	{
	}

	template <I2c T>
	int8_t Temperature<T>::degrees()
	{
		return static_cast<int8_t>(extract_bits(registers, sizeof(registers), 0x00, 0x0, 0x8));
	}

	template <I2c T>
	uint8_t Temperature<T>::quarters()
	{
		return extract_bits(registers, sizeof(registers), 0x00, 0x6, 0x2);
	}

	template <I2c T>
	bool Temperature<T>::retrieve()
	{
		static const uint8_t address = 0x11;

		i2c->blocking_write(0x68, &address, sizeof(address), true);
		return i2c->blocking_read(0x68, registers, sizeof(registers));
	}
}