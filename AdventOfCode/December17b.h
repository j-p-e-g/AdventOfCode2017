#pragma once

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/17

    Part 2:

    [Y]ou actually need to identify the value after 0 in the current state of the circular buffer.

    The bad news is that while you were determining this, the spinlock has just finished inserting its fifty millionth value (50000000).

    What is the value after 0 the moment 50000000 is inserted?
*/

namespace AdventOfCode {
namespace December17 {

    class SpinlockB
        : protected AdventOfCodeBase
    {
    public:
        SpinlockB(const std::string& fileName);
        ~SpinlockB() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        static int CalculateLastValueAtIndexOne(long repeats, int stepSize);
        int GetLastValueAtIndexOne() const;

    private:
        long m_lastValueAtIndexOne = -1;
    };

}
}
