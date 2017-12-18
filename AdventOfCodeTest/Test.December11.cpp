#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December11.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December11;

    TEST_CLASS(Test_December11)
	{
	public:
        // -------------------------
        // ParseLine
        // -------------------------
        /*
        empty
        */
        TEST_METHOD(December11_ParseLine_empty)
        {
            InfiniteHexGrid test;
            Assert::AreEqual(true, test.ParseLine(""));
            Assert::AreEqual(0, test.GetPathLength());
        }

        /*
        invalid direction
        */
        TEST_METHOD(December11_ParseLine_notDirection)
        {
            InfiniteHexGrid test;
            Assert::AreEqual(false, test.ParseLine("bla"));
        }

        /*
        comma-separated without spaces
        */
        TEST_METHOD(December11_ParseLine_validNoSpaces)
        {
            InfiniteHexGrid test;
            Assert::AreEqual(true, test.ParseLine("nw,s,sw,s"));
            Assert::AreEqual(4, test.GetPathLength());
        }

        /*
        comma-separated with spaces
        */
        TEST_METHOD(December11_ParseLine_validWithSpaces)
        {
            InfiniteHexGrid test;
            Assert::AreEqual(true, test.ParseLine("s, se, ne"));
            Assert::AreEqual(3, test.GetPathLength());
        }

        /*
        contains non-direction
        */
        TEST_METHOD(December11_ParseLine_containsNonDir)
        {
            InfiniteHexGrid test;
            Assert::AreEqual(false, test.ParseLine("n,n,sw,k,s"));
        }

        /*
        ends with a dangling comma
        */
        TEST_METHOD(December11_ParseLine_danglingComma)
        {
            InfiniteHexGrid test;
            Assert::AreEqual(false, test.ParseLine("se,se,n,"));
        }

        // ------------------------------------
        // GetTargetCell
        // ------------------------------------
        /*
		empty path
		*/
		TEST_METHOD(December11_GetTargetCell_empty)
		{
			InfiniteHexGrid test(std::vector<std::string>({}));
			Assert::AreEqual(true, Cell(0, 0) == test.GetTargetCell());
            Assert::AreEqual(0, test.GetPathLength());
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
            Assert::AreEqual(4, test.GetPathLength());
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

        // ------------------------------------
        // GetTargetDistanceToOrigin
        // ------------------------------------
        /*
		empty path
		*/
		TEST_METHOD(December11_GetDistance_emptyPath)
		{
			InfiniteHexGrid test(std::vector<std::string>({}));
			Assert::AreEqual(0, test.GetTargetDistanceToOrigin());
		}

        /*
        clockwise circular path -> end up at north cell
        */
        TEST_METHOD(December11_GetDistance_clockwiseCircle)
        {
            InfiniteHexGrid test({ "n", "se", "s", "sw", "nw", "n", "ne" });
            Assert::AreEqual(true, Cell(0, -1) == test.GetTargetCell());
            Assert::AreEqual(1, test.GetTargetDistanceToOrigin());
        }
       
        /*
        counter-clockwise circular path -> end up at se cell
        */
        TEST_METHOD(December11_GetDistance_counterClockwiseCircle)
        {
            InfiniteHexGrid test({ "se", "n", "nw", "sw", "s", "se", "ne" });
            Assert::AreEqual(true, Cell(1, 0) == test.GetTargetCell());
            Assert::AreEqual(1, test.GetTargetDistanceToOrigin());
        }

        /*
        amble along a slightly longer path
        */
        TEST_METHOD(December11_GetDistance_longerPath)
        {
            //      \ n  /              \ (0, -1) /
            //    nw +--+ ne     (-1, 0) +-------+ (1, -1)
            //      /    \              /         \
          	//    -+      +-        ---+  (0, 0)   +---
            //      \    /              \         /
            //    sw +--+ se     (-1, 1) +-------+ (1, 0)
            //      / s  \              / (0, 1)  \

            InfiniteHexGrid test({ "nw", "n", "ne", "ne", "n", "se", "n", "ne" });
            Assert::AreEqual(true, Cell(3, -6) == test.GetTargetCell());
            Assert::AreEqual(6, test.GetTargetDistanceToOrigin());
        }

        /*
        pesky diagonal movement requires a special case when computing the distance
        */
        TEST_METHOD(December11_GetDistance_diagonal)
        {
            InfiniteHexGrid test(std::vector<std::string>({ "nw", "n" }));
            Assert::AreEqual(true, Cell(-1, -1) == test.GetTargetCell());
            Assert::AreEqual(2, test.GetTargetDistanceToOrigin());
        }

        // ----------------------------------
        // GetSimplifiedPath
        // ----------------------------------
        /*
        cannot be simplified
        */
        TEST_METHOD(December11_GetSimplifiedPath_unchanged)
        {
            InfiniteHexGrid test({ "s", "sw", "s" });
            const std::vector<std::string> simplifiedPath = test.GetSimplifiedPath();
            Assert::AreEqual(3, static_cast<int>(simplifiedPath.size()));
        }

        /*
        path cancels itself out entirely
        */
        TEST_METHOD(December11_GetSimplifiedPath_cancelOut)
        {
            InfiniteHexGrid test({ "n", "sw", "ne", "nw", "s", "se" });
            const std::vector<std::string> simplifiedPath = test.GetSimplifiedPath();
            Assert::AreEqual(true, simplifiedPath.empty());
        }

        /*
        zigzagging path is straightened -> becomes n, n
        */
        TEST_METHOD(December11_GetSimplifiedPath_zigzag)
        {
            InfiniteHexGrid test({ "ne", "n", "nw" });
            const std::vector<std::string> simplifiedPath = test.GetSimplifiedPath();
            Assert::AreEqual(2, static_cast<int>(simplifiedPath.size()));
            for (const auto& step : simplifiedPath)
            {
                Assert::AreEqual("n", step.c_str());
            }
        }

        /*
        path gets simplified (cancelation + zigzag) -> becomes se, sw -> s
        */
        TEST_METHOD(December11_GetSimplifiedPath_simplified)
        {
            InfiniteHexGrid test({ "se", "n", "sw", "nw", "se", "s" });
            const std::vector<std::string> simplifiedPath = test.GetSimplifiedPath();
            Assert::AreEqual(1, static_cast<int>(simplifiedPath.size()));
            for (const auto& step : simplifiedPath)
            {
                Assert::AreEqual("s", step.c_str());
            }

            // output should be the same
            InfiniteHexGrid simplifiedTest(simplifiedPath);
            Assert::AreEqual(true, test.GetTargetCell() == simplifiedTest.GetTargetCell());
            Assert::AreEqual(true, test.GetTargetDistanceToOrigin() == simplifiedTest.GetTargetDistanceToOrigin());
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
