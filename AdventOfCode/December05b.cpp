#include "stdafx.h"

#include <iostream>

#include "December05b.h"

using namespace AdventOfCode::December05;

InstructionMazeB::InstructionMazeB(const std::string& fileName)
    : InstructionMaze(fileName)
{
}

void InstructionMazeB::OutputResultToConsole() const
{
    std::cout << "December05.b: result = " << CountInstructionSteps(m_instructions) << std::endl;
}

int InstructionMazeB::CountInstructionSteps(std::vector<int> input)
{
    int count = 0;
    int pos = 0;

    while (pos >= 0 && pos < input.size())
    {
        // Positive jumps ("forward") move downward; negative jumps move upward.
        int nextPos = pos + input[pos];

        // After each jump, if the offset was three or more, decrease it by 1. 
        // Otherwise, increase it by 1.
        if (input[pos] >= 3)
        {
            input[pos]--;
        }
        else
        {
            input[pos]++;
        }

        pos = nextPos;

        count++;
    }

    return count;
}
