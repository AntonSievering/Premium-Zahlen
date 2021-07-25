#pragma once
#include <memory>
#include <cmath>

class BitBuffer
{
	std::shared_ptr<uint8_t> pMemory;
	std::size_t size;

public:
	BitBuffer() noexcept = default;

	BitBuffer(const std::size_t &size) noexcept
	{
		this->size = std::ceil((double)size / 8.0);
		pMemory = std::shared_ptr<uint8_t>(new uint8_t[this->size]{});
	}

public:
	bool getBit(const std::size_t &i)
	{
		const std::size_t b = i / 8;
		const std::size_t o = i % 8;
		const uint8_t mask = 1 << o;

		return (pMemory.get()[b] & mask) > 0;
	}

	uint8_t getByte(const std::size_t i)
	{
		return pMemory.get()[i];
	}

	void setBit(const std::size_t &i)
	{
		const std::size_t b = i / 8;
		const std::size_t o = i % 8;
		const uint8_t mask = 1 << o;
		
		pMemory.get()[b] |= mask;
	}

	void clearBit(const std::size_t &i)
	{
		const std::size_t b = i / 8;
		const std::size_t o = i % 8;
		const uint8_t mask = 1 << o;

		pMemory.get()[b] &= ~mask;
	}

	void clear()
	{
		std::memset(pMemory.get(), 0x00, size);
	}

	void set()
	{
		std::memset(pMemory.get(), 0xFF, size);
	}
};