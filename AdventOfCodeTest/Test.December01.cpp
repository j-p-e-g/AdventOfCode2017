#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December01.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdventOfCodeTest
{		
	TEST_CLASS(Test_December01)
	{
	public:
		/*
		handle empty string
		*/
		TEST_METHOD(December01_String_EmptyString)
		{
			December01 adventClass;
			Assert::AreEqual(0, adventClass.ComputeSumForCaptchaString(""));
		}

		/*
		single digit -> no next digit to match
		*/
		TEST_METHOD(December01_Number_SingleDigit)
		{
			December01 adventClass;
			Assert::AreEqual(0, adventClass.ComputeSumForCaptchaNumber(5));
		}
		TEST_METHOD(December01_String_SingleDigit)
		{
			December01 adventClass;
			Assert::AreEqual(0, adventClass.ComputeSumForCaptchaString("5"));
		}

		/*
		1111 produces 4 because each digit (all 1) matches the next.
		*/
		TEST_METHOD(December01_Number_AllSameDigit)
		{
			December01 adventClass;
			Assert::AreEqual(4, adventClass.ComputeSumForCaptchaNumber(1111));
		}
		TEST_METHOD(December01_String_AllSameDigit)
		{
			December01 adventClass;
			Assert::AreEqual(4, adventClass.ComputeSumForCaptchaString("1111"));
		}

		/*
		1122 produces a sum of 3 (1 + 2) because the first digit (1) matches the second digit and the third digit (2) matches the fourth digit.
		*/
		TEST_METHOD(December01_Number_DoubleDigit)
		{
			December01 adventClass;
			Assert::AreEqual(3, adventClass.ComputeSumForCaptchaNumber(1122));
		}
		TEST_METHOD(December01_String_DoubleDigit)
		{
			December01 adventClass;
			Assert::AreEqual(3, adventClass.ComputeSumForCaptchaString("1122"));
		}

		/*
		1234 produces 0 because no digit matches the next.
		*/
		TEST_METHOD(December01_Number_AllDifferentDigits)
		{
			December01 adventClass;
			Assert::AreEqual(0, adventClass.ComputeSumForCaptchaNumber(1234));
		}
		TEST_METHOD(December01_String_AllDifferentDigits)
		{
			December01 adventClass;
			Assert::AreEqual(0, adventClass.ComputeSumForCaptchaString("1234"));
		}

		/*
		91212129 produces 9 because the only digit that matches the next one is the last digit, 9.
		*/
		TEST_METHOD(December01_Number_OnlyFirstAndLastDigitsMatch)
		{
			December01 adventClass;
			Assert::AreEqual(9, adventClass.ComputeSumForCaptchaNumber(91212129));
		}
		TEST_METHOD(December01_String_OnlyFirstAndLastDigitsMatch)
		{
			December01 adventClass;
			Assert::AreEqual(9, adventClass.ComputeSumForCaptchaString("91212129"));
		}
	};
}