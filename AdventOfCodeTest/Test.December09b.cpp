#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December09b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December09;

    TEST_CLASS(Test_December09b)
    {
    public:
        // ----------------------------------
        // GetTotalGarbageSize
        // ----------------------------------
        TEST_METHOD(December09b_GetTotalGarbageSize_empty)
        {
            StreamGarbageRemoval test(std::stringstream(""));
            Assert::AreEqual(0, test.GetTotalGarbageSize());
        }

        /*
        <>, 0 characters.
        */
        TEST_METHOD(December09b_AoC_GetTotalGarbageSize_test1)
        {
            StreamGarbageRemoval test(std::stringstream("<>"));
            Assert::AreEqual(0, test.GetTotalGarbageSize());
        }

        /*
        <random characters>, 17 characters.
        */
        TEST_METHOD(December09b_AoC_GetTotalGarbageSize_test2)
        {
            StreamGarbageRemoval test(std::stringstream("<random characters>"));
            Assert::AreEqual(17, test.GetTotalGarbageSize());
        }

        /*
        <<<<>, 3 characters.
        */
        TEST_METHOD(December09b_AoC_GetTotalGarbageSize_test3)
        {
            StreamGarbageRemoval test(std::stringstream("<<<<>"));
            Assert::AreEqual(3, test.GetTotalGarbageSize());
        }

        /*
        <{!>}>, 2 characters.
        */
        TEST_METHOD(December09b_AoC_GetTotalGarbageSize_test4)
        {
            StreamGarbageRemoval test(std::stringstream("<{!>}>"));
            // ignore escaped characters
            Assert::AreEqual(2, test.GetTotalGarbageSize());
        }

        /*
        <!!>, 0 characters.
        */
        TEST_METHOD(December09b_AoC_GetTotalGarbageSize_test5)
        {
            StreamGarbageRemoval test(std::stringstream("<!!>"));
            // ignore escaped characters
            Assert::AreEqual(0, test.GetTotalGarbageSize());
        }

        /*
        <!!!>>, 0 characters.
        */
        TEST_METHOD(December09b_AoC_GetTotalGarbageSize_test6)
        {
            StreamGarbageRemoval test(std::stringstream("<!!!>>"));
            // ignore escaped characters
            Assert::AreEqual(0, test.GetTotalGarbageSize());
        }

        /*
        <{o"i!a,<{i<a>, 10 characters.
        */
        TEST_METHOD(December09b_AoC_GetTotalGarbageSize_test7)
        {
            StreamGarbageRemoval test(std::stringstream("<{o\"i!a,<{i<a>"));
            Assert::AreEqual(10, test.GetTotalGarbageSize());
        }
    };
}
