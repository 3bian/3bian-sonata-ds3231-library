#pragma once

namespace DS3231
{
	template <typename T>
	concept I2c = requires(volatile T* t, const uint8_t addr, uint8_t buf[],
		const uint32_t numBytes, const bool skipStop)
	{
		{ t->blocking_read(addr, buf, numBytes) } -> std::same_as<bool>;
		{ t->blocking_write(addr, buf, numBytes, skipStop) } 
		    -> std::same_as<void>;
	};

	inline void assign_bcd_bits(uint8_t* buffer, uint8_t index, uint8_t value,
		uint8_t unitsOffset, uint8_t tensOffset, uint8_t unitsBits,
		uint8_t tensBits);
		
	inline void assign_bits(uint8_t* buffer, uint8_t index, uint8_t offset,
		uint8_t count, uint8_t value);
		
	inline uint8_t extract_bcd_bits(uint8_t* buffer, uint8_t index,
		uint8_t unitsOffset, uint8_t tensOffset, uint8_t unitsBits,
		uint8_t tensBits);
		
	inline uint8_t extract_bits(uint8_t* buffer, uint8_t index, uint8_t offset,
		uint8_t count);

	inline void assign_bcd_bits(uint8_t* buffer, uint8_t index, uint8_t value,
		uint8_t unitsOffset, uint8_t tensOffset, uint8_t unitsBits,
		uint8_t tensBits)
	{
		uint8_t units = value % 10u;
		uint8_t tens  = value / 10u;
		assign_bits(buffer, index, unitsOffset, unitsBits, units);
		assign_bits(buffer, index, tensOffset, tensBits, tens);
	}

	inline void assign_bits(uint8_t* buffer, uint8_t index, uint8_t offset,
		uint8_t count, uint8_t value)
	{
		uint8_t mask = ((1u << count) - 1u) << offset;
		buffer[index] = (buffer[index] & ~mask) | ((value << offset) & mask);
	}

	inline uint8_t extract_bcd_bits(uint8_t* buffer, uint8_t index,
		uint8_t unitsOffset, uint8_t tensOffset, uint8_t unitsBits,
		uint8_t tensBits)
	{
		uint8_t units = extract_bits(buffer, index, unitsOffset, unitsBits);
		uint8_t tens  = extract_bits(buffer, index, tensOffset, tensBits);
		return 10u * tens + units;
	}

	inline uint8_t extract_bits(uint8_t* buffer, uint8_t index, uint8_t offset,
		uint8_t count)
	{
		return (buffer[index] >> offset) & ((1u << count) - 1u);
	}
}