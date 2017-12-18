#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December01b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December01;

    TEST_CLASS(Test_December01b)
    {
    public:
        // --------------------------------
        // ParseLine
        // --------------------------------
        /*
        succeeds for input with an even length
        */
        TEST_METHOD(December01b_ParseLine_even)
        {
            CircularCheckSum test;
            Assert::AreEqual(true, test.ParseLine("4472"));
        }

        /*
        fails for input with an odd length
        */
        TEST_METHOD(December01b_ParseLine_odd)
        {
            CircularCheckSum test;
            Assert::AreEqual(false, test.ParseLine("73892"));
        }

        // --------------------------------
        // ComputeSumForCaptchaString
        // --------------------------------
        /*
        odd-numbered input is invalid
        */
        TEST_METHOD(December01b_ComputeSumForCaptchaString)
        {
            Assert::AreEqual(-1, CircularCheckSum::ComputeSumForCaptchaString("33333"));
        }

        /*
        1212 produces 6: the list contains 4 items, and all four digits match the digit 2 items ahead.
        */
        TEST_METHOD(December01b_AoC_test1)
        {
            Assert::AreEqual(6, CircularCheckSum::ComputeSumForCaptchaString("1212"));
        }

        /*
        1221 produces 0, because every comparison is between a 1 and a 2.
        */
        TEST_METHOD(December01b_AoC_test2)
        {
            Assert::AreEqual(0, CircularCheckSum::ComputeSumForCaptchaString("1221"));
        }

        /*
        123425 produces 4, because both 2s match each other, but no other digit has a match.
        */
        TEST_METHOD(December01b_AoC_test3)
        {
            Assert::AreEqual(4, CircularCheckSum::ComputeSumForCaptchaString("123425"));
        }

        /*
        123123 produces 12.
        */
        TEST_METHOD(December01b_AoC_test4)
        {
            Assert::AreEqual(12, CircularCheckSum::ComputeSumForCaptchaString("123123"));
        }
    };
}
