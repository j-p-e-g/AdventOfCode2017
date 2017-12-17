#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December06.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December06;

    TEST_CLASS(Test_December06)
	{
	public:
        // -------------------------------------
        // ParseLine
        // -------------------------------------
        /*
        handle empty string
        */
        TEST_METHOD(December06_ParseLine_EmptyString)
        {
            MemoryReallocator mem;
            Assert::AreEqual(true, mem.ParseLine(""));
        }

        /*
        invalid: not a number
        */
        TEST_METHOD(December06_ParseLine_nonNumber)
        {
            MemoryReallocator mem;
            Assert::AreEqual(false, mem.ParseLine("edt"));
        }

        /*
        valid: numbers
        */
        TEST_METHOD(December06_ParseLine_valid)
        {
            MemoryReallocator mem;
            Assert::AreEqual(true, mem.ParseLine("-86686 0 0 75"));
        }

        /*
        invalid: row contains non-number
        */
        TEST_METHOD(December06_ParseLine_containsNonNumber)
        {
            MemoryReallocator mem;
            Assert::AreEqual(false, mem.ParseLine("975hf 762"));
        }

        /*
        invalid: comma separated values
        */
        TEST_METHOD(December06_ParseLine_commaSeparated)
        {
            MemoryReallocator mem;
            Assert::AreEqual(false, mem.ParseLine("5, 926, 3, -25, 2"));
        }

        //--------------------------------------------------------
		// GetMaxIndex
		// -------------------------------------------------------
		/*
		empty vector
		*/
		TEST_METHOD(December06_GetMaxIndex_empty)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { };
			Assert::AreEqual(-1, test.GetMaxIndex(memBanks));
		}

		/*
		single value
		*/
		TEST_METHOD(December06_GetMaxIndex_singleValue)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 8 };
			Assert::AreEqual(0, test.GetMaxIndex(memBanks));
		}

		/*
		it finds the memory bank with the most blocks
		*/
		TEST_METHOD(December06_GetMaxIndex_uniqueMaximum)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 4, 5, 3, 2 };
			Assert::AreEqual(1, test.GetMaxIndex(memBanks));
		}

		/*
		it finds the memory bank with the most blocks (ties won by the lowest-numbered memory bank)
		*/
		TEST_METHOD(December06_GetMaxIndex_tiedMaximum)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 7, 5, 7, 9, 4, 9, 9 };
			Assert::AreEqual(3, test.GetMaxIndex(memBanks));
		}

		//--------------------------------------------------------
		// GetNextIndex
		// -------------------------------------------------------
		/*
		empty vector
		*/
		TEST_METHOD(December06_GetNextIndex_empty)
		{
			MemoryReallocator test;
			Assert::AreEqual(-1, test.GetNextIndex(0, 0));
		}

		/*
		single element
		*/
		TEST_METHOD(December06_GetNextIndex_single)
		{
			MemoryReallocator test;
			Assert::AreEqual(0, test.GetNextIndex(0, 1));
		}

		/*
		increase index
		*/
		TEST_METHOD(December06_GetNextIndex_increaseIndex)
		{
			MemoryReallocator test;
			Assert::AreEqual(4, test.GetNextIndex(3, 17));
		}

		/*
		last element -> wrap around
		*/
		TEST_METHOD(December06_GetNextIndex_wrapAround)
		{
			MemoryReallocator test;
			Assert::AreEqual(0, test.GetNextIndex(4, 5));
		}

		//--------------------------------------------------------
		// RunMemoryAllocationCycle
		// -------------------------------------------------------
		/*
		empty
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_empty)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { };
			const MemoryBanks expectedResult = { };

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		/*
		single entry
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_singleValue)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 3497 };
			const MemoryBanks expectedResult = { 3497 };

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		/*
		already balanced becomes unbalanced (it's a stupid algorithm, alright?)
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_alreadyBalanced)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 50, 50 };
			const MemoryBanks expectedResult = {25, 75};

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		/*
		The banks start with 0, 2, 7, and 0 blocks. The third bank has the most blocks, so it is chosen for redistribution.
		Starting with the next bank (the fourth bank) and then continuing to the first bank, the second bank, and so on, the 7 blocks are spread out over the memory banks. The fourth, first, and second banks get two blocks each, and the third bank gets one back. The final result looks like this: 2 4 1 2.
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_1)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 0, 2, 7, 0 };
			const MemoryBanks expectedResult = { 2, 4, 1, 2 };

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		/*
		2 4 1 2.
		Next, the second bank is chosen because it contains the most blocks (four). Because there are four memory banks, each gets one block. The result is: 3 1 2 3.
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_2)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 2, 4, 1, 2 };
			const MemoryBanks expectedResult = { 3, 1, 2, 3 };

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		/*
		3 1 2 3.
		Now, there is a tie between the first and fourth memory banks, both of which have three blocks. The first bank wins the tie, and its three blocks are distributed evenly over the other three banks, leaving it with none: 0 2 3 4.
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_3)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 3, 1, 2, 3 };
			const MemoryBanks expectedResult = { 0, 2, 3, 4 };

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		/*
		0 2 3 4.
		The fourth bank is chosen, and its four blocks are distributed such that each of the four banks receives one: 1 3 4 1.
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_4)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 0, 2, 3, 4 };
			const MemoryBanks expectedResult = { 1, 3, 4, 1 };

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		/*
		1 3 4 1.
		The third bank is chosen, and the same thing happens: 2 4 1 2.
		*/
		TEST_METHOD(December06_RunMemoryAllocationCycle_5)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 1, 3, 4, 1 };
			const MemoryBanks expectedResult = { 2, 4, 1, 2 };

			test.RunMemoryAllocationCycle(memBanks);

			Assert::AreEqual(expectedResult.size(), memBanks.size());
			for (int k = 0; k < expectedResult.size(); k++)
			{
				Assert::AreEqual(expectedResult[k], memBanks[k]);
			}
		}

		//--------------------------------------------------------
		// CountCyclesUntilStuck
		// -------------------------------------------------------
		/*
		empty vector
		*/
		TEST_METHOD(December06_CountCyclesUntilStuck_empty)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { };
			Assert::AreEqual(1, test.CountCyclesUntilStuck(memBanks));
		}

		/*
		single entry
		*/
		TEST_METHOD(December06_CountCyclesUntilStuck_single)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 15 };
			Assert::AreEqual(1, test.CountCyclesUntilStuck(memBanks));
		}

		/*
		all zero
		*/
		TEST_METHOD(December06_CountCyclesUntilStuck_allZero)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 0, 0, 0, 0, 0, 0 };
			Assert::AreEqual(1, test.CountCyclesUntilStuck(memBanks));
		}

		/*
		already balanced
		*/
		TEST_METHOD(December06_CountCyclesUntilStuck_alreadyBalanced)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = { 10, 10 };
			Assert::AreEqual(4, test.CountCyclesUntilStuck(memBanks));
		}

		//--------------------------------------------------------
		// Advent of Code example
		// -------------------------------------------------------
		/*
		The banks start with 0, 2, 7, and 0 blocks. [...]
		The infinite loop is detected after the fifth block redistribution cycle, and so the answer in this example is 5.
		*/
		TEST_METHOD(December06_AoC_test)
		{
			MemoryReallocator test;
			MemoryBanks memBanks = {0, 2, 7, 0};
			Assert::AreEqual(5, test.CountCyclesUntilStuck(memBanks));
		}
	};
}

