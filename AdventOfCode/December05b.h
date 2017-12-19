#pragma once

#include "December05.h"

/*
    https://adventofcode.com/2017/day/5

    Part 2:

    Now, the jumps are even stranger: after each jump, if the offset was three or more, instead decrease it by 1. Otherwise, increase it by 1 as before.

        Using this rule with the above example, the process now takes 10 steps, and the offset values after finding the exit are left as 2 3 2 3 -1.

    How many steps does it now take to reach the exit?
*/

namespace AdventOfCode {
namespace December05 {

    class InstructionMazeB
        : protected InstructionMaze
    {
    public:
        InstructionMazeB() {};
        InstructionMazeB(const std::string& fileName);
        ~InstructionMazeB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        static int CountInstructionSteps(std::vector<int> input);
    };

}}
