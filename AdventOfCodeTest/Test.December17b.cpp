#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December17b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December17;

    TEST_CLASS(Test_December17b)
    {
    public:
        TEST_METHOD(December17_GetLastValueAtIndexOne_0)
        {
            // 0
            Assert::AreEqual(-1, SpinlockB::CalculateLastValueAtIndexOne(0, 5));
        }

        TEST_METHOD(December17_GetLastValueAtIndexOne_1)
        {
            // 0 1
            Assert::AreEqual(1, SpinlockB::CalculateLastValueAtIndexOne(1, 186));
        }

        TEST_METHOD(December17_GetLastValueAtIndexOne_3)
        {
            // 0 2 3 1
            Assert::AreEqual(2, SpinlockB::CalculateLastValueAtIndexOne(3, 3));
        }

        TEST_METHOD(December17_GetLastValueAtIndexOne_7)
        {
            // 0 5 7 2 4 3 6 1
            Assert::AreEqual(5, SpinlockB::CalculateLastValueAtIndexOne(7, 3));
        }

        TEST_METHOD(December17_GetLastValueAtIndexOne_9)
        {
            // 0 9 5 7 2 4 3 8 6 1
            Assert::AreEqual(9, SpinlockB::CalculateLastValueAtIndexOne(9, 3));
        }
    };
}
