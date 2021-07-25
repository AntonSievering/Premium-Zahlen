#include <stdint.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include "BitBuffer.h"
#include "Timer.h"

void prime(const uint64_t &nTo)
{
	std::ofstream file = std::ofstream("E:/output.log");
	file.clear();

	BitBuffer buffer = BitBuffer(nTo);
	buffer.set();
	buffer.clearBit(0);
	buffer.clearBit(1);

	Engine::Timer timer = Engine::Timer().start();

	uint64_t sqrtSize = ceil(sqrt((double)nTo));
	for (uint64_t i = 2; i <= sqrtSize; i++)
		if (buffer.getBit(i))
			for (uint64_t j = 2 * i; j < nTo; j += i)
				buffer.clearBit(j);

	std::cout << "computed primes in " << timer.getElapsedTime() << "s\n";
	
	constexpr uint64_t nCacheSize = 1ui64 << 20;
	constexpr uint64_t nCacheSizeOffset = 1ui64 << 10;
	std::string sBuffer;
	sBuffer.reserve(nCacheSize);

	timer.start();

	uint64_t nPrimes = 0;
	for (uint64_t i = 2; i < nTo; i++)
		if (buffer.getBit(i))
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

#define GiB 1024 * 1024 * 1024

int main()
{
	prime(1e9);
}
