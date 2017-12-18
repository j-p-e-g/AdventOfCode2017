#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December02.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December02;

    TEST_CLASS(Test_December02)
	{
	public:
        // -------------------------------------
        // ParseLine
        // -------------------------------------
        /*
        handle empty string
        */
        TEST_METHOD(December02_ParseLine_EmptyString)
        {
            MatrixCheckSum matrix;
            Assert::AreEqual(true, matrix.ParseLine(""));
        }

        /*
        empty row
        */
        TEST_METHOD(December02_ParseLine_emptyRow)
        {
            MatrixCheckSum matrix;
            Assert::AreEqual(true, matrix.ParseLine("\n\n"));
        }

        /*
        invalid: not a number
        */
        TEST_METHOD(December02_ParseLine_nonNumber)
        {
            MatrixCheckSum matrix;
            Assert::AreEqual(false, matrix.ParseLine("796skhg"));
        }

        /*
        valid: numbers
        */
        TEST_METHOD(December02_ParseLine_valid)
        {
            MatrixCheckSum matrix;
            Assert::AreEqual(true, matrix.ParseLine("97 -3 515968926"));
        }

        /*
        invalid: row contains non-number
        */
        TEST_METHOD(December02_ParseLine_containsNonNumber)
        {
            MatrixCheckSum matrix;
            Assert::AreEqual(false, matrix.ParseLine("18 947 lklh"));
        }

        /*
        invalid: comma separated values
        */
        TEST_METHOD(December02_ParseLine_commaSeparated)
        {
            MatrixCheckSum matrix;
            Assert::AreEqual(false, matrix.ParseLine("6, 3, 27"));
        }

        // ------------------------------------
        // GetRowCheckSum
        // ------------------------------------
        /*
		handle empty row
		*/
		TEST_METHOD(December02_EmptyRow)
		{
            MatrixCheckSum test;
            MatrixRow row;

			Assert::AreEqual(0, test.GetRowCheckSum(row));
		}

		/*
		handle single value row
		*/
		TEST_METHOD(December02_SingleValueRow)
		{
            MatrixCheckSum test;
            MatrixRow row = { 8 };
			Assert::AreEqual(0, test.GetRowCheckSum(row));
		}

		/*
		handle single negative value row
		*/
		TEST_METHOD(December02_SingleNegativeValueRow)
		{
            MatrixCheckSum test;
            MatrixRow row = { -5 };
			Assert::AreEqual(0, test.GetRowCheckSum(row));
		}

		/*
		handle identical value row
		*/
		TEST_METHOD(December02_IdenticalValueRow)
		{
            MatrixCheckSum test;
            MatrixRow row = { 3, 3, 3, 3, 3, 3 };
			Assert::AreEqual(0, test.GetRowCheckSum(row));
		}

		/*
		handle identical negative value row
		*/
		TEST_METHOD(December02_IdenticalNegativeValueRow)
		{
            MatrixCheckSum test;
            MatrixRow row = { -93, -93 };
			Assert::AreEqual(0, test.GetRowCheckSum(row));
		}

		/*
		5 1 9 5
		The first row's largest and smallest values are 9 and 1, and their difference is 8.
		*/
		TEST_METHOD(December02_CheckSumRow)
		{
            MatrixCheckSum test;
            MatrixRow row = { 5, 1, 9, 5 };
			Assert::AreEqual(8, test.GetRowCheckSum(row));
		}

		/*
        the row minimum is negative, the maximum positive
		*/
		TEST_METHOD(December02_CheckSumNegativeRow)
		{
            MatrixCheckSum test;
            MatrixRow row = { 4, -8, -9, 2, 15 };
			Assert::AreEqual(24, test.GetRowCheckSum(row));
		}

        // ------------------------------------
        // GetMatrixCheckSum
        // ------------------------------------
		/*
		handle empty matrix
		*/
		TEST_METHOD(December02_EmptyMatrix)
		{
            MatrixCheckSum test;
            Matrix matrix;
			Assert::AreEqual(0, test.GetMatrixCheckSum(matrix));
		}

		/*
		handle matrix consisting of empty rows
		*/
		TEST_METHOD(December02_MatrixOfEmptyRows)
		{
            MatrixCheckSum test;
            MatrixRow row1;
			MatrixRow row2;
			Matrix matrix = { row1, row2 };

			Assert::AreEqual(0, test.GetMatrixCheckSum(matrix));
		}

		/*
		handle single row
		*/
		TEST_METHOD(December02_SingleRowMatrix)
		{
            MatrixCheckSum test;
            MatrixRow row = { 7, 35, 30656 };
			Matrix matrix = { row };

			Assert::AreEqual(test.GetRowCheckSum(row), test.GetMatrixCheckSum(matrix));
		}

		/*
		For example, given the following spreadsheet:

		5 1 9 5
		7 5 3
		2 4 6 8

		The first row's largest and smallest values are 9 and 1, and their difference is 8.
		The second row's largest and smallest values are 7 and 3, and their difference is 4.
		The third row's difference is 6.

		In this example, the spreadsheet's checksum would be 8 + 4 + 6 = 18.
		*/
		TEST_METHOD(December02_CheckSumMatrix)
		{
            MatrixCheckSum test;
            MatrixRow row1 = {5, 1, 9, 5};
			MatrixRow row2 = { 7, 5, 3 };
			MatrixRow row3 = { 2, 4, 6, 8 };
			Matrix matrix = { row1, row2, row3 };

			Assert::AreEqual(18, test.GetMatrixCheckSum(matrix));
		}

	};
}