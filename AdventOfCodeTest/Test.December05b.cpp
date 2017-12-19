#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December05b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December05;

    TEST_CLASS(Test_December05b)
    {
    public:
        /*
        requires one extra step than in the previous version
        */
        TEST_METHOD(December05b_CountInstructionSteps_decreaseFor3)
        {
            InstructionMaze testa;
            Assert::AreEqual(3, testa.CountInstructionSteps({ 3, 0, 2, -3 }));
            InstructionMazeB test;
            Assert::AreEqual(4, test.CountInstructionSteps({ 3, 0, 2, -3 }));
        }

        /*
        For example, consider the following list of jump offsets:

        0
        3
        0
        1
        -3

        Using this rule with the above example, the process now takes 10 steps, and the offset values after finding the exit are left as 2 3 2 3 -1.
        */
        TEST_METHOD(December05b_AoC_test)
        {
            InstructionMazeB test;
            Assert::AreEqual(10, test.CountInstructionSteps({0, 3, 0, 1, -3}));
        }
    };
}
