#pragma once
#include <cstdint>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>

uint64_t sieb(uint64_t nFrom, uint64_t nTo, std::fstream* file) noexcept
{
	uint64_t nSize = nTo - nFrom;
	bool *pSieb = new bool[nSize];
	memset(pSieb, 1, nSize);

	for (uint64_t i = 2; i <= ceil(sqrt((double)nTo)); i++)
		if (pSieb[i])
			for (uint64_t j = 2 * i; j <= nTo; j += i)
				if (j >= nFrom + 2)
					pSieb[j - nFrom - 2] = false;

	std::cout << "calculation done" << std::endl;

	uint64_t n = 0;
	if (file->is_open())
	{
		for (uint64_t i = nFrom; i < nTo - 1; i++)
		{
			if (pSieb[i - nFrom])
			{
				*file << std::to_string(i + 2) << std::endl;
				n++;
			}
		}
		std::cout << "found " << n << " prime numbers in the bounds of " << nFrom << " to " << nTo << std::endl;
	}

	delete[] pSieb;
	return n;
}

void prime(uint64_t nTo)
{
	system("type nul > output.log");
	std::fstream *file = new std::fstream("output.log");
	file->clear();

	uint64_t nFound = 0;
	uint64_t nSteps = ceil((double)nTo / 1e10);

	for (uint64_t i = 0; i < nSteps; i++)
	{
		uint64_t from = i * 1e10;
		uint64_t to = (i + 1) * 1e10;
		if (to > nTo)
			to = nTo;

		nFound += sieb(from, to, file);
	}

	std::cout << "total prime numbers in the range to " << nTo << ": " << nFound << std::endl;
}