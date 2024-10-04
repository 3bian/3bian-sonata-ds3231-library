#pragma once

#include <concepts>
#include <cstdint>

template <typename T>
concept I2cConcept = requires(T* i2c, const uint8_t addr, uint8_t buf[],
    const uint32_t numBytes, const bool skipStop)
{
    { i2c->blocking_read(addr, buf, numBytes) } -> std::same_as<bool>;
    { i2c->blocking_write(addr, buf, numBytes, skipStop) } -> std::same_as<void>;
};

template<uint8_t offset, uint8_t count>
inline void assign_bits(uint8_t* byte, uint8_t value)
{
    static_assert((offset + count) <= 8, "Invalid bit range in assign");
    uint8_t mask = ((1u << count) - 1u) << offset;
    *byte = (*byte & ~mask) | ((value << offset) & mask);
}

template<uint8_t offset, uint8_t count>
inline uint8_t extract_bits(const uint8_t byte)
{
    static_assert((offset + count) <= 8, "Invalid bit range in extract");
    return byte >> offset) & ((1u << count) - 1u);
}
