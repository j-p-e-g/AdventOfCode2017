#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/CoordPoint.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace Coord;

    TEST_CLASS(Test_CoordPoint)
    {
    public:
        /*
        Compare two points with various comparison operators.
        */
        TEST_METHOD(CoordPoint_Compare_XY_same)
        {
            Coord::Point p1(13, 25972);
            Coord::Point p2(13, 25972);

            Assert::AreEqual(true, p1 == p2);
            Assert::AreEqual(true, p1 >= p2);
            Assert::AreEqual(true, p1 <= p2);
            Assert::AreEqual(false, p1 > p2);
            Assert::AreEqual(false, p1 < p2);
        }

        TEST_METHOD(CoordPoint_Compare_X_same_Y_different)
        {
            Coord::Point p1(728, -15);
            Coord::Point p2(728, -12);

            Assert::AreEqual(false, p1 == p2);
            Assert::AreEqual(false, p1 >= p2);
            Assert::AreEqual(true, p1 <= p2);
            Assert::AreEqual(false, p1 > p2);
            Assert::AreEqual(true, p1 < p2);
            // compare in the other direction
            Assert::AreEqual(true, p2 >= p1);
            Assert::AreEqual(false, p2 <= p1);
            Assert::AreEqual(true, p2 > p1);
            Assert::AreEqual(false, p2 < p1);
        }

        TEST_METHOD(CoordPoint_Compare_X_different_Y_same)
        {
            Coord::Point p1(-19, -2);
            Coord::Point p2(-22, -2);

            Assert::AreEqual(false, p1 == p2);
            Assert::AreEqual(true, p1 >= p2);
            Assert::AreEqual(false, p1 <= p2);
            Assert::AreEqual(true, p1 > p2);
            Assert::AreEqual(false, p1 < p2);
            // compare in the other direction
            Assert::AreEqual(false, p2 >= p1);
            Assert::AreEqual(true, p2 <= p1);
            Assert::AreEqual(false, p2 > p1);
            Assert::AreEqual(true, p2 < p1);
        }

        TEST_METHOD(CoordPoint_Compare_XY_different_sameDir)
        {
            Coord::Point p1(-28, 99);
            Coord::Point p2(55, 101);

            Assert::AreEqual(false, p1 == p2);
            Assert::AreEqual(false, p1 >= p2);
            Assert::AreEqual(true, p1 <= p2);
            Assert::AreEqual(false, p1 > p2);
            Assert::AreEqual(true, p1 < p2);
            // compare in the other direction
            Assert::AreEqual(true, p2 >= p1);
            Assert::AreEqual(false, p2 <= p1);
            Assert::AreEqual(true, p2 > p1);
            Assert::AreEqual(false, p2 < p1);
        }

        TEST_METHOD(CoordPoint_Compare_XY_different_opposingDir)
        {
            Coord::Point p1(78, 5);
            Coord::Point p2(14, 24);

            Assert::AreEqual(false, p1 == p2);
            Assert::AreEqual(true, p1 >= p2);
            Assert::AreEqual(false, p1 <= p2);
            Assert::AreEqual(true, p1 > p2);
            Assert::AreEqual(false, p1 < p2);
            // compare in the other direction
            Assert::AreEqual(false, p2 >= p1);
            Assert::AreEqual(true, p2 <= p1);
            Assert::AreEqual(false, p2 > p1);
            Assert::AreEqual(true, p2 < p1);
        }

        /*
        Basic math.
        */
        TEST_METHOD(CoordPoint_Add)
        {
            Coord::Point p1(-9, 18);
            Coord::Point p2(8, 4);

            p1 += p2;
            Assert::AreEqual(-1, p1.x);
            Assert::AreEqual(22, p1.y);
        }

        TEST_METHOD(CoordPoint_MultiplyConstant)
        {
            Coord::Point p(17, -4);

            p *= 2;
            Assert::AreEqual(34, p.x);
            Assert::AreEqual(-8, p.y);

            p *= -3;
            Assert::AreEqual(-102, p.x);
            Assert::AreEqual(24, p.y);
        }

        TEST_METHOD(CoordPoint_AddTwoPoints)
        {
            Coord::Point p1(7, 3);
            Coord::Point p2(-4, 2);

            Coord::Point sum = p1 + p2;
            Assert::AreEqual(3, sum.x);
            Assert::AreEqual(5, sum.y);
        }
    };
}
