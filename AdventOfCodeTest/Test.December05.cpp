#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December05.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December05;

    TEST_CLASS(Test_December05)
	{
	public:
		TEST_METHOD(December05_empty)
		{
            Assert::AreEqual(0, InstructionMaze::CountInstructionSteps({}));
		}

		TEST_METHOD(December05_justZero)
		{
            Assert::AreEqual(2, InstructionMaze::CountInstructionSteps({ 0 }));
		}

		TEST_METHOD(December05_justPositive)
		{
            Assert::AreEqual(1, InstructionMaze::CountInstructionSteps({ 3 }));
        }

		TEST_METHOD(December05_justNegative)
		{
            Assert::AreEqual(1, InstructionMaze::CountInstructionSteps({ -73 }));
        }

		TEST_METHOD(December05_vector)
		{
            Assert::AreEqual(3, InstructionMaze::CountInstructionSteps({ 5, 4, 3, -3, -4, -5 }));
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
            Assert::AreEqual(5, InstructionMaze::CountInstructionSteps({ 0, 3, 0, 1, -3 }));
        }
	};
}

