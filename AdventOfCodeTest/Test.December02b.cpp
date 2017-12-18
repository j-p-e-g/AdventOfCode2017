#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December02b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December02;

    TEST_CLASS(Test_December02b)
    {
    public:
        // -------------------------------
        // GetRowCheckSum
        // -------------------------------
        /*
        empty row
        */
        TEST_METHOD(December02b_GetRowCheckSum_empty)
        {
            MatrixCheckSumMultiple test;
            MatrixRow row = { };

            Assert::AreEqual(0, test.GetRowCheckSum(row));
        }

        /*
        no multiples
        */
        TEST_METHOD(December02b_GetRowCheckSum_noMultiple)
        {
            MatrixCheckSumMultiple test;
            MatrixRow row = {2, 5, 7};

            Assert::AreEqual(0, test.GetRowCheckSum(row));
        }

        /*
        the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
        */
        TEST_METHOD(December02b_GetRowCheckSum_test1)
        {
            MatrixCheckSumMultiple test;
            MatrixRow row = { 5, 9, 2, 8 };

            Assert::AreEqual(4, test.GetRowCheckSum(row));
        }

        /*
        the two numbers are 9 and 3; the result is 3
        */
        TEST_METHOD(December02b_GetRowCheckSum_test2)
        {
            MatrixCheckSumMultiple test;
            MatrixRow row = { 9, 4, 7, 3 };

            Assert::AreEqual(3, test.GetRowCheckSum(row));
        }

        // -------------------------------
        // GetMatrixCheckSum
        // -------------------------------
        /*
        5 9 2 8
        9 4 7 3
        3 8 6 5

        In the first row, the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
        In the second row, the two numbers are 9 and 3; the result is 3.
        In the third row, the result is 2.

        In this example, the sum of the results would be 4 + 3 + 2 = 9.
        */
        TEST_METHOD(December02b_AoC_test)
        {
            MatrixCheckSumMultiple test;
            MatrixRow row1 = { 5, 9, 2, 8 };
            MatrixRow row2 = { 9, 4, 7, 3 };
            MatrixRow row3 = { 3, 8, 6, 5 };
            Matrix matrix = { row1, row2, row3 };

            Assert::AreEqual(9, test.GetMatrixCheckSum(matrix));
        }
    };
}
