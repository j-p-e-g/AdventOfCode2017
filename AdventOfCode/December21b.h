#pragma once

#include <set>

#include "December21.h"

/*
    https://adventofcode.com/2017/day/21

    Part 2:

    How many pixels stay on after 18 iterations?

    NOTE: Obviously, this requires some kind of optimization again...
*/
namespace AdventOfCode {
namespace December21 {

    class PixelPatternB
        : public PixelPattern
    {
    public:
        PixelPatternB() {};
        PixelPatternB(const std::string& fileName);
        ~PixelPatternB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        bool ProcessRules(int numIterations) override;
        int ApplyRulesToMatrix(std::shared_ptr<Matrix::CharMatrix>& matrix, int numIterations, bool first);

    private:
        std::map<std::string, std::map<int, std::string> > m_4x4Transformations;
        std::map<std::string, std::string> m_4x4Rotations;
    };

}}
