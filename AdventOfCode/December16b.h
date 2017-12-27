#pragma once

#include <map>

#include "December16.h"

/*
    https://adventofcode.com/2017/day/16

    Part 2:

    Now that you're starting to get a feel for the dance moves, you turn your attention to the dance as a whole.

    Keeping the positions they ended up in from their previous dance, the programs perform it again and again: including the first dance, a total of one billion (1000000000) times.

        In the example above, their second dance would begin with the order baedc, and use the same dance moves:

        s1, a spin of size 1: cbaed.
        x3/4, swapping the last two programs: cbade.
        pe/b, swapping programs e and b: ceadb.

    In what order are the programs standing after their billion dances?
*/

namespace AdventOfCode {
namespace December16 {

    class ProgramDancingMasterB
        : public ProgramDancingMaster
    {
    public:
        ProgramDancingMasterB(int size = 16, long long numRepeats = 1000000000);
        ProgramDancingMasterB(const std::string& fileName, int size = 16, long long numRepeats = 1000000000);
        ~ProgramDancingMasterB() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    private:
        long long m_numRepetitions;
        std::map<std::string, int> m_formations;
    };

}}
