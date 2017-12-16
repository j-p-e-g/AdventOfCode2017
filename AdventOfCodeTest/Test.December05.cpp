#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December05.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace December05;

namespace AdventOfCodeTest
{
	TEST_CLASS(Test_December05)
	{
	public:
		TEST_METHOD(December05_empty)
		{
			InstructionMaze test;
			std::vector<int> input = { };
			Assert::AreEqual(0, test.CountInstructionSteps(input));
		}

		TEST_METHOD(December05_justZero)
		{
			InstructionMaze test;
			std::vector<int> input = { 0 };
			Assert::AreEqual(2, test.CountInstructionSteps(input));
		}

		TEST_METHOD(December05_justPositive)
		{
			InstructionMaze test;
			std::vector<int> input = { 3 };
			Assert::AreEqual(1, test.CountInstructionSteps(input));
		}

		TEST_METHOD(December05_justNegative)
		{
			InstructionMaze test;
			std::vector<int> input = { -73 };
			Assert::AreEqual(1, test.CountInstructionSteps(input));
		}

		TEST_METHOD(December05_vector)
		{
			InstructionMaze test;
			std::vector<int> input = { 5, 4, 3, -3, -4, -5 };
			Assert::AreEqual(3, test.CountInstructionSteps(input));
		}

		/*
		(0) 3  0  1  -3  - before we have taken any steps.
		(1) 3  0  1  -3  - jump with offset 0 (that is, don't jump at all). Fortunately, the instruction is then incremented to 1.
		2 (3) 0  1  -3  - step forward because of the instruction we just modified. The first instruction is incremented again, now to 2.
		2  4  0  1 (-3) - jump all the way to the end; leave a 4 behind.
		2 (4) 0  1  -2  - go back to where we just were; increment -3 to -2.
		2  5  0  1  -2  - jump 4 steps forward, escaping the maze.

		In this example, the exit is reached in 5 steps.
		*/
		TEST_METHOD(December05_AoC_Test)
		{
			InstructionMaze test;
			std::vector<int> input = {0, 3, 0, 1, -3};
			Assert::AreEqual(5, test.CountInstructionSteps(input));
		}
	};
}

