
#pragma once

#include "December02.h"

/*
    https://adventofcode.com/2017/day/2

    Part 2:

    the goal is to find the only two numbers in each row where one evenly divides the other - that is, where the result of the division operation is a whole number. They would like you to find those numbers on each line, divide them, and add up each line's result.

    For example, given the following spreadsheet:

        5 9 2 8
        9 4 7 3
        3 8 6 5

        In the first row, the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
        In the second row, the two numbers are 9 and 3; the result is 3.
        In the third row, the result is 2.

        In this example, the sum of the results would be 4 + 3 + 2 = 9.

    What is the sum of each row's result in your puzzle input?
*/

namespace AdventOfCode {
namespace December02 {

    class MatrixCheckSumMultiple
        : public MatrixCheckSum
    {
    public:
        MatrixCheckSumMultiple() {};
        MatrixCheckSumMultiple(const std::string& fileName);
        ~MatrixCheckSumMultiple() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        virtual int GetRowCheckSum(const MatrixRow& row) const;
    };

}}
