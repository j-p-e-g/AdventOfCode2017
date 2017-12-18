#pragma once

#include "December01.h"

/*
    https://adventofcode.com/2017/day/1

    Part 2:

    Now, instead of considering the next digit, it wants you to consider the digit halfway around the circular list. That is, if your list contains 10 items, only include a digit in your sum if the digit 10/2 = 5 steps forward matches it. Fortunately, your list has an even number of elements.

    For example:

        1212 produces 6: the list contains 4 items, and all four digits match the digit 2 items ahead.
        1221 produces 0, because every comparison is between a 1 and a 2.
        123425 produces 4, because both 2s match each other, but no other digit has a match.
        123123 produces 12.
        12131415 produces 4.

    What is the solution to your new captcha?
*/

namespace AdventOfCode {
namespace December01 {

    class CircularCheckSum
        : protected CheckSum
    {
    public:
        CircularCheckSum() {};
        CircularCheckSum(const std::string& fileName);
        ~CircularCheckSum() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        static int ComputeSumForCaptchaString(const std::string& captchaString);

    };

}}
