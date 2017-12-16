#include "stdafx.h"
#include "December05.h"

using namespace December05;

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
