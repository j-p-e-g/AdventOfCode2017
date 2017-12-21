#pragma once

#include <map>

#include "December03.h"

/*
    https://adventofcode.com/2017/day/3

    Part 2:

    As a stress test on the system, the programs here clear the grid and then store the value 1 in square 1. Then, in the same allocation order as shown above, they store the sum of the values in all adjacent squares, including diagonals.

    So, the first few squares' values are chosen as follows:

        Square 1 starts with the value 1.
        Square 2 has only one adjacent filled square (with value 1), so it also stores 1.
        Square 3 has both of the above squares as neighbors and stores the sum of their values, 2.
        Square 4 has all three of the aforementioned squares as neighbors and stores the sum of their values, 4.
        Square 5 only has the first and fourth squares as neighbors, so it gets the value 5.

    Once a square is written, its value does not change. Therefore, the first few squares would receive the following values:

        147  142  133  122   59
        304    5    4    2   57
        330   10    1    1   54
        351   11   23   25   26
        362  747  806--->   ...

    What is the first value written that is larger than your puzzle input?
*/
namespace AdventOfCode {
namespace December03 {

    class SumSpiralMemory
        : protected SpiralMemory
    {
    public:
        SumSpiralMemory() {};
        SumSpiralMemory(const std::string& fileName);
        ~SumSpiralMemory() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        // computes the summed values along the spiral until a value greater than m_value is reached
        // then returns that value
        int ConstructMapUntilValuePassed(int value);
        int GetSumOfAdjacentPoints(const CodeUtils::Point& p) const;

    private:
        int m_greaterValue;
        std::map<CodeUtils::Point, int> m_pointMap;
    };

}}
