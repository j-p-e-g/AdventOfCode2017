#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December03b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December03;

    TEST_CLASS(Test_December03b)
    {
    public:
        // -------------------------------------
        // GetSumOfAdjacentPoints
        // -------------------------------------
        TEST_METHOD(December03b_GetSumOfAdjacentPoints_empty)
        {
            SumSpiralMemory test;
            // no points ever added -> sum is zero
            Assert::AreEqual(0, test.GetSumOfAdjacentPoints(Coord::Point(3, -4)));
        }

        TEST_METHOD(December03b_GetSumOfAdjacentPoints_test1)
        {
            SumSpiralMemory test;
            test.ConstructMapUntilValuePassed(50);
            // after construction (all adjacent points in map) -> sum of all neighbours
            Assert::AreEqual(81, test.GetSumOfAdjacentPoints(Coord::Point(0,0)));
            // before construction (would have been the next point to be added to the map)
            Assert::AreEqual(54, test.GetSumOfAdjacentPoints(Coord::Point(2,0)));
        }

        // -------------------------------------
        // ConstructMapUntilValuePassed
        // -------------------------------------
        /*
        147  142  133  122   59
        304    5    4    2   57
        330   10    1    1   54
        351   11   23   25   26
        362  747  806--->   ...
        */
        TEST_METHOD(December03b_GetFirstGreaterValue_test1)
        {
            SumSpiralMemory test;
            Assert::AreEqual(2, test.ConstructMapUntilValuePassed(1));
        }

        TEST_METHOD(December03b_GetFirstGreaterValue_test2)
        {
            SumSpiralMemory test;
            Assert::AreEqual(26, test.ConstructMapUntilValuePassed(25));
        }

        TEST_METHOD(December03b_GetFirstGreaterValue_test3)
        {
            SumSpiralMemory test;
            Assert::AreEqual(747, test.ConstructMapUntilValuePassed(500));
        }
    };
}
