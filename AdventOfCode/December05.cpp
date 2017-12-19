#include "stdafx.h"

#include <iostream>

#include "CodeUtil.h"
#include "December05.h"

using namespace AdventOfCode::December05;

InstructionMaze::InstructionMaze(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool InstructionMaze::ParseLine(const std::string& inputLine)
{
    int value = -1;
    if (CodeUtils::CodeUtil::ReadStringToInt(inputLine, value, true))
    {
        AddInstruction(atoi(inputLine.c_str()));
        return true;
    }

    return false;
}

void InstructionMaze::AddInstruction(int number)
{
    m_instructions.push_back(number);
}

void InstructionMaze::OutputResultToConsole() const
{
    std::cout << "December05.a: result = " << CountInstructionSteps(m_instructions) << std::endl;
}

int InstructionMaze::CountInstructionSteps(std::vector<int> input)
{
	int count = 0;
	int pos = 0;

	while (pos >= 0 && pos < input.size())
	{
		// Positive jumps ("forward") move downward; negative jumps move upward.
		int nextPos = pos + input[pos];
		// after each jump, the offset of that instruction increases by 1
		input[pos]++;
		pos = nextPos;

		count++;
	}

	return count;
}
