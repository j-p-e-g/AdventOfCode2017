#include "stdafx.h"
#include "December06.h"

#include <set>

using namespace December06;

/*
In each cycle, it finds the memory bank with the most blocks (ties won by the lowest-numbered memory bank)
*/
int MemoryReallocator::GetMaxIndex(const MemoryBanks& memBanks)
{
	int maxIndex = -1;
	for (int k = 0; k < memBanks.size(); k++)
	{
		if (maxIndex == -1 || memBanks[k] > memBanks[maxIndex])
		{
			maxIndex = k;
		}
	}

	return maxIndex;
}

int MemoryReallocator::GetNextIndex(int currentIndex, int maxSize)
{
	if (maxSize <= 0)
	{
		return -1;
	}

	return (currentIndex + 1) % maxSize;
}

/*
The reallocation routine operates in cycles. In each cycle, it finds the memory bank with the most blocks (ties won by the lowest-numbered memory bank) and redistributes those blocks among the banks. To do this, it removes all of the blocks from the selected bank, then moves to the next (by index) memory bank and inserts one of the blocks. It continues doing this until it runs out of blocks; if it reaches the last memory bank, it wraps around to the first one.
*/
void MemoryReallocator::RunMemoryAllocationCycle(MemoryBanks& memBanks)
{
	const int maxIndex = GetMaxIndex(memBanks);
	if (maxIndex < 0 || maxIndex >= memBanks.size())
	{
		return;
	}

	// clear max. entry
	int remaining = memBanks[maxIndex];
	memBanks[maxIndex] = 0;

	// ... and redistribute it across the vector
	int index = GetNextIndex(maxIndex, static_cast<int>(memBanks.size()));
	while (remaining > 0)
	{
		memBanks[index]++;
		remaining--;
		index = GetNextIndex(index, static_cast<int>(memBanks.size()));
	}
}

int MemoryReallocator::CountCyclesUntilStuck(const MemoryBanks& memBanks)
{
	std::set<MemoryBanks> seenSetups;

	MemoryBanks currentSetup = memBanks;
	while (seenSetups.find(currentSetup) == seenSetups.end())
	{
		seenSetups.emplace(currentSetup);
		RunMemoryAllocationCycle(currentSetup);
	}

	return static_cast<int>(seenSetups.size());
}
