#pragma once

#include <memory>
#include <vector>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/17

    Part 1:

    This spinlock's algorithm is simple but efficient, quickly consuming everything in its path. It starts with a circular buffer containing only the value 0, which it marks as the current position. It then steps forward through the circular buffer some number of steps (your puzzle input) before inserting the first new value, 1, after the value it stopped on. The inserted value becomes the current position. Then, it steps forward from there the same number of steps, and wherever it stops, inserts after it the second new value, 2, and uses that as the new current position again.

    It repeats this process of stepping forward, inserting a new value, and using the location of the inserted value as the new current position a total of 2017 times, inserting 2017 as its final operation, and ending with a total of 2018 values (including 0) in the circular buffer.

        For example, if the spinlock were to step 3 times per insert, the circular buffer would begin to evolve like this (using parentheses to mark the current position after each iteration of the algorithm):

        (0), the initial state before any insertions.
        0 (1): the spinlock steps forward three times (0, 0, 0), and then inserts the first value, 1, after it. 1 becomes the current position.
        0 (2) 1: the spinlock steps forward three times (0, 1, 0), and then inserts the second value, 2, after it. 2 becomes the current position.
        0  2 (3) 1: the spinlock steps forward three times (1, 0, 2), and then inserts the third value, 3, after it. 3 becomes the current position.

    And so on:

        0  2 (4) 3  1
        0 (5) 2  4  3  1
        0  5  2  4  3 (6) 1
        0  5 (7) 2  4  3  6  1
        0  5  7  2  4  3 (8) 6  1
        0 (9) 5  7  2  4  3  8  6  1

        Eventually, after 2017 insertions, the section of the circular buffer near the last insertion looks like this:

        1512  1134  151 (2017) 638  1513  851

    Perhaps, if you can identify the value that will ultimately be after the last value written (2017), you can short-circuit the spinlock. 

        In this example, that would be 638.

    What is the value after 2017 in your completed circular buffer?
*/

namespace AdventOfCode {
namespace December17 {

    class CircularVector
    {
    public:
        CircularVector(const std::vector<int>& initialState, int initialIndex = 0);

    public:
        bool InsertAfterCurrentIndexWithOffset(int value, int offset);
        int GetNextValue() const;
        int GetCurrentIndex() const { return m_currentIndex; }
        int GetSize() const { return static_cast<int>(m_vector.size()); }
        void GetVector(std::vector<int>& result);

    private:
        int m_currentIndex = -1;
        std::vector<int> m_vector;

    };

    class Spinlock
        : protected AdventOfCodeBase
    {
    public:
        Spinlock();
        Spinlock(const std::string& fileName);
        ~Spinlock() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        void StartSpinlock(int stepSize, int repeats);
        int GetNextValue() const;
        void GetVector(std::vector<int>& result) const;

    private:
        std::shared_ptr<CircularVector> m_circularVector;
    };

}}