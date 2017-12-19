#pragma once

#include "December06.h"

/*
    https://adventofcode.com/2017/day/6

    Part 2:

    Out of curiosity, the debugger would also like to know the size of the loop: starting from a state that has already been seen, how many block redistribution cycles must be performed before that same state is seen again?

        In the example above, 2 4 1 2 is seen again after four cycles, and so the answer in that example would be 4.

    How many cycles are in the infinite loop that arises from the configuration in your puzzle input?
*/

namespace AdventOfCode {
namespace December06 {

    class MemoryReallocatorCycleCount
        : protected MemoryReallocator
    {
    public:
        MemoryReallocatorCycleCount() {};
        MemoryReallocatorCycleCount(const std::string& fileName);
        ~MemoryReallocatorCycleCount() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        int CountCyclesUntilRepeat(const MemoryBanks& memBanks) const;
    };

}}
