#pragma once

#include "December11.h"

/*
    https://adventofcode.com/2017/day/11

    Part 2:

    How many steps away is the furthest he ever got from his starting position?
*/

namespace AdventOfCode {
namespace December11 {

    class InfiniteHexGridB
        : public InfiniteHexGrid
    {
    public:
        InfiniteHexGridB(const std::vector<std::string>& path);
        InfiniteHexGridB(const std::string& fileName);
        ~InfiniteHexGridB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        int GetMaxDistanceFromOriginEver() const;
    };

}}
