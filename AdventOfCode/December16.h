#pragma once

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/16

    Part 1:

    You come upon a very unusual sight; a group of programs here appear to be dancing.

    There are sixteen programs in total, named a through p. They start by standing in a line: a stands in position 0, b stands in position 1, and so on until p, which stands in position 15.

    The programs' dance consists of a sequence of dance moves:

    Spin, written sX, makes X programs move from the end to the front, but maintain their order otherwise. (For example, s3 on abcde produces cdeab).
    Exchange, written xA/B, makes the programs at positions A and B swap places.
    Partner, written pA/B, makes the programs named A and B swap places.

        For example, with only five programs standing in a line (abcde), they could do the following dance:

        s1, a spin of size 1: eabcd.
        x3/4, swapping the last two programs: eabdc.
        pe/b, swapping programs e and b: baedc.

        After finishing their dance, the programs end up in order baedc.

    You watch the dance for a while and record their dance moves (your puzzle input). In what order are the programs standing after their dance?
*/

namespace AdventOfCode {
namespace December16 {

    class ProgramDancingMaster
        : protected AdventOfCodeBase
    {
    public:
        ProgramDancingMaster(int size = 16);
        ProgramDancingMaster(const std::string& fileName, int size = 16);
        ~ProgramDancingMaster() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        bool ApplyDancingMove(const std::string& move);
        bool ApplySpin(int length);
        bool ApplyPartner(char char1, char char2);
        bool ApplySwap(int id1, int id2);
        std::string GetFinalFormation() const;

    private:
        std::string m_dancingFormation;
    };

}}
