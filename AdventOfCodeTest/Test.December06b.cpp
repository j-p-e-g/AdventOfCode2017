#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December06b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December06;

    TEST_CLASS(Test_December06b)
    {
    public:
        /*
        empty list -> repeats immediately
        */
        TEST_METHOD(December06b_CountCyclesUntilRepeat_empty)
        {
            MemoryReallocatorCycleCount test;
            MemoryBanks memBanks = {};
            Assert::AreEqual(1, test.CountCyclesUntilRepeat(memBanks));
        }

        /*
        single value -> repeats immediately
        */
        TEST_METHOD(December06b_CountCyclesUntilRepeat_single)
        {
            MemoryReallocatorCycleCount test;
            MemoryBanks memBanks = { 8 };
            Assert::AreEqual(1, test.CountCyclesUntilRepeat(memBanks));
        }

        /*
        imbalanced -> becomes 5, 5 -> 3, 7 -> 6, 4 -> 3, 7
        */
        TEST_METHOD(December06b_CountCyclesUntilRepeat_imbalanced)
        {
            MemoryReallocatorCycleCount test;
            MemoryBanks memBanks = { 0, 10 };
            Assert::AreEqual(2, test.CountCyclesUntilRepeat(memBanks));
        }

        /*
        already balanced -> becomes 6, 2 -> 3, 5 -> 5, 3 -> 3, 5
        */
        TEST_METHOD(December06b_CountCyclesUntilRepeat_balanced)
        {
            MemoryReallocatorCycleCount test;
            MemoryBanks memBanks = { 4, 4 };
            Assert::AreEqual(2, test.CountCyclesUntilRepeat(memBanks));
        }

        /*
        The banks start with 0, 2, 7, and 0 blocks. [...]

        In the example above, 2 4 1 2 is seen again after four cycles, and so the answer in that example would be 4.
        */
        TEST_METHOD(December06b_AoC_test)
        {
            MemoryReallocatorCycleCount test;
            MemoryBanks memBanks = { 0, 2, 7, 0 };
            Assert::AreEqual(4, test.CountCyclesUntilRepeat(memBanks));
        }
    };
}
