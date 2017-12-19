#include "stdafx.h"

#include <iostream>
#include <map>

#include "December06b.h"

using namespace AdventOfCode::December06;

MemoryReallocatorCycleCount::MemoryReallocatorCycleCount(const std::string& fileName)
    : MemoryReallocator(fileName)
{
}

void MemoryReallocatorCycleCount::OutputResultToConsole() const
{
    std::cout << "December06.b: result = " << CountCyclesUntilRepeat(m_memory) << std::endl;
}

int MemoryReallocatorCycleCount::CountCyclesUntilRepeat(const MemoryBanks& memBanks) const
{
    // keep track of the first time each setup was seen
    std::map<MemoryBanks, int> seenSetups;

    int timeCounter = 0;
    MemoryBanks currentSetup = memBanks;

    while (true)
    {
        const auto& found = seenSetups.find(currentSetup);
        if (found != seenSetups.end())
        {
            // how many cycles happened since the same setup was first seen
            return timeCounter - found->second;
        }

        seenSetups.emplace(currentSetup, timeCounter);
        RunMemoryAllocationCycle(currentSetup);
        timeCounter++;
    }
}
