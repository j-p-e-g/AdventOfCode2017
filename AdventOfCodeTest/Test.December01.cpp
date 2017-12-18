#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December01.h"

namespace AdventOfCodeTest
{		
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December01;

	TEST_CLASS(Test_December01)
	{
	public:
        // -------------------------------------
        // Parse numbers
        // -------------------------------------
        /*
        handle empty string
        */
        TEST_METHOD(December01_String_EmptyString)
        {
            CheckSum checkSum;
            checkSum.ParseLine("");
            Assert::AreEqual(0, checkSum.GetNumber());
            Assert::AreEqual(0, checkSum.ComputeCheckSum());
        }

        /*
        not a number
        */
        TEST_METHOD(December01_String_NotANumber)
        {
            CheckSum checkSum;
            checkSum.ParseLine("9xgh5");
            Assert::AreEqual(0, checkSum.GetNumber());
        }

        /*
        valid number
        */
        TEST_METHOD(December01_String_IsANumber)
        {
            CheckSum checkSum;
            checkSum.ParseLine("743367");
            Assert::AreEqual(743367, checkSum.GetNumber());
        }

        // -------------------------------------
        // ComputeSum, given a string
        // -------------------------------------
        /*
        single digit -> no next digit to match
        */
        TEST_METHOD(December01_String_SingleDigit)
		{
			CheckSum checkSum;
            checkSum.ParseLine("7");
            Assert::AreEqual(0, checkSum.ComputeCheckSum());
		}

        /*
        each digits matches the next
        */
        TEST_METHOD(December01_String_AllSameDigit)
		{
            CheckSum checkSum;
            checkSum.ParseLine("3333");
			Assert::AreEqual(12, checkSum.ComputeCheckSum());
		}

        /*
        two digits each match the next one
        */
		TEST_METHOD(December01_String_DoubleDigit)
		{
            CheckSum checkSum;
            checkSum.ParseLine("4422");
			Assert::AreEqual(6, checkSum.ComputeCheckSum());
		}

        /*
        each digit is unique
        */
		TEST_METHOD(December01_String_AllDifferentDigits)
		{
            CheckSum checkSum;
            checkSum.ParseLine("7589");
            Assert::AreEqual(0, checkSum.ComputeCheckSum());
		}

        /*
        digits repeat, but not consecutively
        */
        TEST_METHOD(December01_String_NonConsecutiveRepeats)
        {
            CheckSum checkSum;
            checkSum.ParseLine("51515151");
            Assert::AreEqual(0, checkSum.ComputeCheckSum());
        }

        /*
        the first and last digits match
        */
        TEST_METHOD(December01_String_OnlyFirstAndLastDigitsMatch)
		{
            CheckSum checkSum;
            checkSum.ParseLine("3679483");
            Assert::AreEqual(3, checkSum.ComputeCheckSum());
		}
	};
}