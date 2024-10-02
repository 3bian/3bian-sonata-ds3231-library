// Copyright 3bian Limited and CHERIoT Contributors.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <ds3231-common.hh>

namespace DS3231
{
	template <I2c T>
	class Control
	{
	public:
		Control(volatile T* i2c);

		bool alarm1_interrupt_enable();
		void set_alarm1_interrupt_enable(bool enable);

		bool alarm2_interrupt_enable();
		void set_alarm2_interrupt_enable(bool enable);

		bool interrupt_control();
		void set_interrupt_control(bool enable);

		bool rate_select1();
		void set_rate_select1(bool enable);

		bool rate_select2();
		void set_rate_select2(bool enable);

		bool convert_temperature();
		void set_convert_temperature(bool enable);

		bool battery_backed_square_wave_enable();
		void set_battery_backed_square_wave_enable(bool enable);

		bool disable_oscillator();
		void set_disable_oscillator(bool enable);

		bool retrieve();
		void store();

	private:
		volatile T* i2c;
		uint8_t registers[1];
	};

	template <I2c T>
	Control<T>::Control(volatile T* i2c)
		: i2c(i2c), registers{}
	{
	}

	template <I2c T>
	bool Control<T>::alarm1_interrupt_enable()
	{
		return extract_bits(registers, 0x00, 0x0, 0x1);
	}

	template <I2c T>
	void Control<T>::set_alarm1_interrupt_enable(bool enable)
	{
		assign_bits(registers, 0x00, 0x0, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::alarm2_interrupt_enable()
	{
		return extract_bits(registers, 0x00, 0x1, 0x1);
	}

	template <I2c T>
	void Control<T>::set_alarm2_interrupt_enable(bool enable)
	{
		assign_bits(registers, 0x00, 0x1, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::interrupt_control()
	{
		return extract_bits(registers, 0x00, 0x2, 0x1);
	}

	template <I2c T>
	void Control<T>::set_interrupt_control(bool enable)
	{
		assign_bits(registers, 0x00, 0x2, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::rate_select1()
	{
		return extract_bits(registers, 0x00, 0x3, 0x1);
	}

	template <I2c T>
	void Control<T>::set_rate_select1(bool enable)
	{
		assign_bits(registers, 0x00, 0x3, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::rate_select2()
	{
		return extract_bits(registers, 0x00, 0x4, 0x1);
	}

	template <I2c T>
	void Control<T>::set_rate_select2(bool enable)
	{
		assign_bits(registers, 0x00, 0x4, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::convert_temperature()
	{
		return extract_bits(registers, 0x00, 0x5, 0x1);
	}

	template <I2c T>
	void Control<T>::set_convert_temperature(bool enable)
	{
		assign_bits(registers, 0x00, 0x5, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::battery_backed_square_wave_enable()
	{
		return extract_bits(registers, 0x00, 0x6, 0x1);
	}

	template <I2c T>
	void Control<T>::set_battery_backed_square_wave_enable(bool enable)
	{
		assign_bits(registers, 0x00, 0x6, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::disable_oscillator()
	{
		return extract_bits(registers, 0x00, 0x7, 0x1);
	}

	template <I2c T>
	void Control<T>::set_disable_oscillator(bool enable)
	{
		assign_bits(registers, 0x00, 0x7, 0x1, enable ? 1 : 0);
	}

	template <I2c T>
	bool Control<T>::retrieve()
	{
		static const uint8_t address = 0x0E;

		i2c->blocking_write(0x68, &address, sizeof(address), true);
		return i2c->blocking_read(0x68, registers, sizeof(registers));
	}

	template <I2c T>
	void Control<T>::store()
	{
		static const uint8_t address = 0x0E;

		uint8_t writeBuffer[sizeof(registers) + 1];
		writeBuffer[0] = address;
		writeBuffer[1] = registers[0];
		i2c->blocking_write(0x68, writeBuffer, sizeof(writeBuffer), true);
	}
}