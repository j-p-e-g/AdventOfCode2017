#pragma once

#include "December23.h"

/*
https://adventofcode.com/2017/day/23

Part 2:

The debug mode switch is wired directly to register a. You flip the switch, which makes register a now start at 1 when the program is executed.

Immediately, the coprocessor begins to overheat. Whoever wrote this program obviously didn't choose a very efficient implementation. You'll need to optimize the program if it has any hope of completing before Santa needs that printer working.

The coprocessor's ultimate goal is to determine the final value left in register h once the program completes. Technically, if it had that... it wouldn't even need to run the program.

After setting register a to 1, if the program were to run to completion, what value would be left in register h?
*/

namespace AdventOfCode {
namespace December23 {

    class RegisterHandlerB
        : public RegisterHandler
    {
    public:
        RegisterHandlerB() {};
        RegisterHandlerB(const std::string& fileName);
        ~RegisterHandlerB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase
    };

    /*
    # Pseudo-code:

     b = 108100
     c = 125100

    # note that c never changes after this!

    h = 0

    vector<int> primes = getAllPrimesUpTo(c)

    # now things get dynamic :

    for (; b <= c; b += 17)
    {
        if (not b in primes)
        {
            h++
        }
    }
    */

    class SimplifiedRegisterHandlerB
        : public AdventOfCodeBase
    {
    public:
        SimplifiedRegisterHandlerB() {};
        ~SimplifiedRegisterHandlerB() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

        void CalculatePrimesUpToValue(const int upperLimit, std::vector<int>& primes) const;
        int CountNonPrimes(int start = 108100, int target = 125100, int step = 17) const;
    };

}}
