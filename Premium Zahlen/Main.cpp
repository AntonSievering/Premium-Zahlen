#include <stdint.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include "BitBuffer.h"
#include "Timer.h"

void prime(const uint64_t nLimit, const std::string &sOutputFilename) noexcept
{
	std::ofstream file = std::ofstream(sOutputFilename);
	file.clear();

	BitBuffer dataBuffer = BitBuffer(nLimit);
	dataBuffer.set();
	dataBuffer.clearBit(0);
	dataBuffer.clearBit(1);

	Engine::Timer timer = Engine::Timer().start();

	uint64_t sqrtSize = std::floor(std::sqrt((double)nLimit));
	for (uint64_t i = 2; i <= sqrtSize; i++)
		if (dataBuffer.getBit(i))
			for (uint64_t j = 2 * i; j < nLimit; j += i)
				dataBuffer.clearBit(j);

	std::cout << "computed primes in " << timer.getElapsedTime() << "s\n";

	constexpr uint64_t nCacheSize = 1ui64 << 20;
	constexpr uint64_t nCacheSizeOffset = 1ui64 << 10; // "unused" fraction of the buffer, so it does not overflow
	std::string sBuffer;
	sBuffer.reserve(nCacheSize);

	timer.start();

	uint64_t nPrimes = 0;
	for (uint64_t i = 2; i < nLimit; i++)
		if (dataBuffer.getBit(i))
		{
			sBuffer += std::to_string(i) + "\n";

			if (sBuffer.size() > nCacheSize - nCacheSizeOffset)
			{
				file.write(sBuffer.c_str(), sBuffer.size());
				sBuffer.clear();
			}

			nPrimes++;
		}
	file.write(sBuffer.c_str(), sBuffer.size());
	file.close();

	std::cout << "found " << nPrimes << " primes in " << timer.getElapsedTime() << "s\n";
}

int main()
{
	prime(1e9, "E:/output.log");
}
