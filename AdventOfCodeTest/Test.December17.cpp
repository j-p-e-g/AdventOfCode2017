#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December17.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December17;

    TEST_CLASS(Test_December17)
    {
    public:
        // -----------------------------
        // CircularVector::InsertWithOffset
        //------------------------------

        /*
        empty circular vector
        */
        TEST_METHOD(December17_CircularVector_unchanged)
        {
            CircularVector test({}, 0);

            std::vector<int> result;
            test.GetVector(result);

            Assert::AreEqual(true, result.empty());
            Assert::AreEqual(-1, test.GetNextValue());
        }

        /*
        attempt to insert a value with a negative offset
        */
        TEST_METHOD(December17_InsertWithOffset_negativeOffset)
        {
            CircularVector test({}, 0);
            Assert::AreEqual(false, test.InsertAfterCurrentIndexWithOffset(25, -1));
            Assert::AreEqual(-1, test.GetNextValue());
        }

        /*
        start with empty vector, insert a value
        */
        TEST_METHOD(December17_InsertWithOffset_empty)
        {
            CircularVector test({}, 0);
            Assert::AreEqual(true, test.InsertAfterCurrentIndexWithOffset(3, 15));

            std::vector<int> result;
            test.GetVector(result);

            // (3)
            Assert::AreEqual(1, static_cast<int>(result.size()));
            Assert::AreEqual(3, result[0]);
            Assert::AreEqual(3, test.GetNextValue());
        }

        /*
        start with a non-empty vector, insert a value with offset 0
        */
        TEST_METHOD(December17_InsertWithOffset_start)
        {
            CircularVector test({13}, 0);
            test.InsertAfterCurrentIndexWithOffset(21, 0);

            std::vector<int> result;
            test.GetVector(result);

            // 13 (21)
            Assert::AreEqual(2, static_cast<int>(result.size()));
            Assert::AreEqual(13, result[0]);
            Assert::AreEqual(21, result[1]);
            Assert::AreEqual(1, test.GetCurrentIndex());
            Assert::AreEqual(13, test.GetNextValue());
        }

        /*
        insert a value in the middle of a non-empty vector
        */
        TEST_METHOD(December17_InsertWithOffset_middle)
        {
            CircularVector test({ 55, 23, 719 }, 0);
            test.InsertAfterCurrentIndexWithOffset(4, 1);

            std::vector<int> result;
            test.GetVector(result);

            // 55 23 (4) 719
            Assert::AreEqual(4, static_cast<int>(result.size()));
            Assert::AreEqual(55, result[0]);
            Assert::AreEqual(23, result[1]);
            Assert::AreEqual(4, result[2]);
            Assert::AreEqual(719, result[3]);
            Assert::AreEqual(2, test.GetCurrentIndex());
            Assert::AreEqual(719, test.GetNextValue());
        }

        /*
        insert a value at the end of a non-empty vector with an odd offset
        */
        TEST_METHOD(December17_InsertWithOffset_end_oddOffset)
        {
            CircularVector test({ 2, 63 }, 0);
            test.InsertAfterCurrentIndexWithOffset(99, 1);

            std::vector<int> result;
            test.GetVector(result);

            // 2 63 (99)
            Assert::AreEqual(3, static_cast<int>(result.size()));
            Assert::AreEqual(2, result[0]);
            Assert::AreEqual(63, result[1]);
            Assert::AreEqual(99, result[2]);
            Assert::AreEqual(2, test.GetCurrentIndex());
            Assert::AreEqual(2, test.GetNextValue());
        }

        /*
        insert a value at the end of a non-empty vector with an even offset
        */
        TEST_METHOD(December17_InsertWithOffset_end_evenOffset)
        {
            CircularVector test({ 9, 52 }, 0);
            test.InsertAfterCurrentIndexWithOffset(14, 8);

            std::vector<int> result;
            test.GetVector(result);

            // 9 (14) 52
            Assert::AreEqual(3, static_cast<int>(result.size()));
            Assert::AreEqual(9, result[0]);
            Assert::AreEqual(14, result[1]);
            Assert::AreEqual(52, result[2]);
            Assert::AreEqual(1, test.GetCurrentIndex());
            Assert::AreEqual(52, test.GetNextValue());
        }

        /*
        insert a value with offset zero when the starting index is non-zero
        */
        TEST_METHOD(December17_InsertWithOffset_differentStart)
        {
            CircularVector test({ 6, 7 }, 1);
            test.InsertAfterCurrentIndexWithOffset(33, 0);

            std::vector<int> result;
            test.GetVector(result);

            // 6 7 (33)
            Assert::AreEqual(3, static_cast<int>(result.size()));
            Assert::AreEqual(6, result[0]);
            Assert::AreEqual(7, result[1]);
            Assert::AreEqual(33, result[2]);
            Assert::AreEqual(2, test.GetCurrentIndex());
            Assert::AreEqual(6, test.GetNextValue());
        }

        /*
        insert a value with non-zero offset when the starting index is non-zero
        */
        TEST_METHOD(December17_InsertWithOffset_differentStart_beyondEnd)
        {
            CircularVector test({ 1001, 86, 3 }, 1);
            test.InsertAfterCurrentIndexWithOffset(87, 2);

            std::vector<int> result;
            test.GetVector(result);

            // 1001, (87), 86, 3
            Assert::AreEqual(4, static_cast<int>(result.size()));
            Assert::AreEqual(1001, result[0]);
            Assert::AreEqual(87, result[1]);
            Assert::AreEqual(86, result[2]);
            Assert::AreEqual(3, result[3]);
            Assert::AreEqual(1, test.GetCurrentIndex());
            Assert::AreEqual(86, test.GetNextValue());
        }

        // -----------------------------
        // Spinlock::ParseLine
        //------------------------------
        /*
        try to parse the empty line
        */
        TEST_METHOD(December17_ParseLine_empty)
        {
            Spinlock test;
            Assert::AreEqual(false, test.ParseLine(""));
        }

        /*
        try to parse a non-number
        */
        TEST_METHOD(December17_ParseLine_nonNumber)
        {
            Spinlock test;
            Assert::AreEqual(false, test.ParseLine("klh"));
        }

        /*
        try to parse a negative number
        */
        TEST_METHOD(December17_ParseLine_negativeNumber)
        {
            Spinlock test;
            Assert::AreEqual(false, test.ParseLine("-5"));
        }

        /*
        parse a positive number
        */
        TEST_METHOD(December17_ParseLine_valid)
        {
            Spinlock test;
            Assert::AreEqual(true, test.ParseLine("86275425"));
        }

        // -----------------------------
        // Spinlock::GetNextValue
        //------------------------------
        /*
        (0), the initial state before any insertions.
        */
        TEST_METHOD(December17_GetNextValue_empty)
        {
            Spinlock test;
            Assert::AreEqual(0, test.GetNextValue());
        }

        /*
        0 (1): the spinlock steps forward three times (0, 0, 0), and then inserts the first value, 1, after it. 1 becomes the current position.
        */
        TEST_METHOD(December17_GetNextValue_AoC_test1)
        {
            Spinlock test;
            test.StartSpinlock(3, 1);
            Assert::AreEqual(0, test.GetNextValue());
        }

        /*
        For example, if the spinlock were to step 3 times per insert, the circular buffer would begin to evolve like this (using parentheses to mark the current position after each iteration of the algorithm):

        (0), the initial state before any insertions.
        0 (1): the spinlock steps forward three times (0, 0, 0), and then inserts the first value, 1, after it. 1 becomes the current position.
        0 (2) 1: the spinlock steps forward three times (0, 1, 0), and then inserts the second value, 2, after it. 2 becomes the current position.
        0  2 (3) 1: the spinlock steps forward three times (1, 0, 2), and then inserts the third value, 3, after it. 3 becomes the current position.
        */
        TEST_METHOD(December17_GetNextValue_AoC_test3)
        {
            Spinlock test;
            test.StartSpinlock(3, 3);

            // 0, 2, (3), 1
            std::vector<int> result;
            test.GetVector(result);
            Assert::AreEqual(4, static_cast<int>(result.size()));

            Assert::AreEqual(1, test.GetNextValue());
            
            Assert::AreEqual(0, result[0]);
            Assert::AreEqual(2, result[1]);
            Assert::AreEqual(3, result[2]);
            Assert::AreEqual(1, result[3]);
        }

        /*
        run 9 rounds
        */
        TEST_METHOD(December17_GetNextValue_AoC_test9)
        {
            Spinlock test;
            test.StartSpinlock(3, 9);

            // 0 (9) 5  7  2  4  3  8  6  1
            std::vector<int> result;
            test.GetVector(result);
            Assert::AreEqual(10, static_cast<int>(result.size()));

            Assert::AreEqual(5, test.GetNextValue());

            Assert::AreEqual(0, result[0]);
            Assert::AreEqual(9, result[1]);
            Assert::AreEqual(5, result[2]);
            Assert::AreEqual(7, result[3]);
            Assert::AreEqual(2, result[4]);
            Assert::AreEqual(4, result[5]);
            Assert::AreEqual(3, result[6]);
            Assert::AreEqual(8, result[7]);
            Assert::AreEqual(6, result[8]);
            Assert::AreEqual(1, result[9]);
        }

        /*
        Eventually, after 2017 insertions, the section of the circular buffer near the last insertion looks like this:

        1512  1134  151 (2017) 638  1513  851
        */
        TEST_METHOD(December17_GetNextValue_AoC_test2017)
        {
            Spinlock test;
            test.StartSpinlock(3, 2017);
            Assert::AreEqual(638, test.GetNextValue());
        }
    };
}
