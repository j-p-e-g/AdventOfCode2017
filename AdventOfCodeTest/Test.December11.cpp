#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December11.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace December11;

namespace AdventOfCodeTest
{
	TEST_CLASS(Test_December11)
	{
	public:
		/*
		empty path
		*/
		TEST_METHOD(December11_GetTargetCell_empty)
		{
			InfiniteHexGrid test({});
			Assert::AreEqual(true, Cell(0, 0) == test.GetTargetCell());
		}

		/*
		ne,ne,ne is 3 steps away.
		*/
		TEST_METHOD(December11_GetTargetCell_1)
		{
			InfiniteHexGrid test({ "ne", "ne", "ne" });
			Assert::AreEqual(true, Cell(3,-3) == test.GetTargetCell());
		}

		/*
		ne,ne,sw,sw is 0 steps away (back where you started).
		*/
		TEST_METHOD(December11_GetTargetCell_2)
		{
			InfiniteHexGrid test({ "ne", "ne", "sw", "sw" });
			Assert::AreEqual(true, Cell(0, 0) == test.GetTargetCell());
		}

		/*
		ne,ne,s,s is 2 steps away (se,se).
		*/
		TEST_METHOD(December11_GetTargetCell_3)
		{
			InfiniteHexGrid test({ "ne", "ne", "s", "s" });
			Assert::AreEqual(true, Cell(2, 0) == test.GetTargetCell());
		}

		/*
		se,sw,se,sw,sw is 3 steps away (s,s,sw).
		*/
		TEST_METHOD(December11_GetTargetCell_4)
		{
			InfiniteHexGrid test({ "se", "sw", "se", "sw", "sw" });
			Assert::AreEqual(true, Cell(-1, 3) == test.GetTargetCell());
		}

		/*
		se,sw,se,sw,sw is 3 steps away (s,s,sw).
		*/
		TEST_METHOD(December11_GetDistance_emptyPath)
		{
			InfiniteHexGrid test({});
			Assert::AreEqual(0, test.GetTargetDistanceToOrigin());
		}

		// ----------------------------------
		// Advent of Code samples
		// ----------------------------------
		/*
		ne,ne,ne is 3 steps away.
		*/
		TEST_METHOD(December11_AoC_test1)
		{
			InfiniteHexGrid test({"ne", "ne", "ne"});
			Assert::AreEqual(3, test.GetTargetDistanceToOrigin());
		}

		/*
		ne,ne,sw,sw is 0 steps away (back where you started).
		*/
		TEST_METHOD(December11_AoC_test2)
		{
			InfiniteHexGrid test({ "ne", "ne", "sw", "sw" });
			Assert::AreEqual(0, test.GetTargetDistanceToOrigin());
		}

		/*
		ne,ne,s,s is 2 steps away (se,se).
		*/
		TEST_METHOD(December11_AoC_test3)
		{
			InfiniteHexGrid test({ "ne", "ne", "s", "s" });
			Assert::AreEqual(2, test.GetTargetDistanceToOrigin());
		}

		/*
		se,sw,se,sw,sw is 3 steps away (s,s,sw).
		*/
		TEST_METHOD(December11_AoC_test4)
		{
			InfiniteHexGrid test({ "se", "sw", "se", "sw", "sw" });
			Assert::AreEqual(3, test.GetTargetDistanceToOrigin());
		}
	};
}
