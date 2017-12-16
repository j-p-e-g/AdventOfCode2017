#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December02.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace December02;

namespace AdventOfCodeTest
{
	TEST_CLASS(Test_December02)
	{
	public:
		/*
		handle empty row
		*/
		TEST_METHOD(December02_EmptyRow)
		{
			MatrixRow row;

			CheckSum adventClass;
			Assert::AreEqual(0, adventClass.GetCheckSum(row));
		}

		/*
		handle single value row
		*/
		TEST_METHOD(December02_SingleValueRow)
		{
			MatrixRow row = { 8 };

			CheckSum adventClass;
			Assert::AreEqual(0, adventClass.GetCheckSum(row));
		}

		/*
		handle single negative value row
		*/
		TEST_METHOD(December02_SingleNegativeValueRow)
		{
			MatrixRow row = { -5 };

			CheckSum adventClass;
			Assert::AreEqual(0, adventClass.GetCheckSum(row));
		}

		/*
		handle identical value row
		*/
		TEST_METHOD(December02_IdenticalValueRow)
		{
			MatrixRow row = { 3, 3, 3, 3, 3, 3 };

			CheckSum adventClass;
			Assert::AreEqual(0, adventClass.GetCheckSum(row));
		}

		/*
		handle identical negative value row
		*/
		TEST_METHOD(December02_IdenticalNegativeValueRow)
		{
			MatrixRow row = { -93, -93 };

			CheckSum adventClass;
			Assert::AreEqual(0, adventClass.GetCheckSum(row));
		}

		/*
		5 1 9 5
		The first row's largest and smallest values are 9 and 1, and their difference is 8.
		*/
		TEST_METHOD(December02_CheckSumRow)
		{
			MatrixRow row = { 5, 1, 9, 5 };

			CheckSum adventClass;
			Assert::AreEqual(8, adventClass.GetCheckSum(row));
		}

		/*
		5 1 9 5
		The first row's largest and smallest values are 9 and 1, and their difference is 8.
		*/
		TEST_METHOD(December02_CheckSumNegativeRow)
		{
			MatrixRow row = { 4, -8, -9, 2, 15 };

			CheckSum adventClass;
			Assert::AreEqual(24, adventClass.GetCheckSum(row));
		}

		/*
		handle empty matrix
		*/
		TEST_METHOD(December02_EmptyMatrix)
		{
			Matrix matrix;

			CheckSum adventClass;
			Assert::AreEqual(0, adventClass.GetCheckSum(matrix));
		}

		/*
		handle matrix consisting of empty rows
		*/
		TEST_METHOD(December02_MatrixOfEmptyRows)
		{
			MatrixRow row1;
			MatrixRow row2;
			Matrix matrix = { row1, row2 };

			CheckSum adventClass;
			Assert::AreEqual(0, adventClass.GetCheckSum(matrix));
		}

		/*
		handle single row
		*/
		TEST_METHOD(December02_SingleRowMatrix)
		{
			MatrixRow row = { 7, 35, 30656 };
			Matrix matrix = { row };

			CheckSum adventClass;
			Assert::AreEqual(adventClass.GetCheckSum(row), adventClass.GetCheckSum(matrix));
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
			MatrixRow row1 = {5, 1, 9, 5};
			MatrixRow row2 = { 7, 5, 3 };
			MatrixRow row3 = { 2, 4, 6, 8 };
			Matrix matrix = { row1, row2, row3 };

			CheckSum adventClass;
			Assert::AreEqual(18, adventClass.GetCheckSum(matrix));
		}

	};
}