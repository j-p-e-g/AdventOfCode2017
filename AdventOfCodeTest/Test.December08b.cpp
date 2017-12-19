#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December08b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December08;

    TEST_CLASS(Test_December08b)
    {
    public:
        // -------------------------------
        // ApplyCommand
        // -------------------------------
        /*
        try applying invalid commands
        */
        TEST_METHOD(December08b_ApplyCommand_invalidCommand)
        {
            RegisterHandlerB test;
            Assert::AreEqual(false, test.ApplyCommand("ghs set 7"));
            Assert::AreEqual(false, test.RegisterExists("ghs"));
        }

        TEST_METHOD(December08b_ApplyCommand_tooFewParameters1)
        {
            RegisterHandlerB test;
            Assert::AreEqual(false, test.ApplyCommand("dec 612"));
        }

        TEST_METHOD(December08b_ApplyCommand_tooFewParameters2)
        {
            RegisterHandlerB test;
            Assert::AreEqual(false, test.ApplyCommand("tz inc"));
            Assert::AreEqual(false, test.RegisterExists("tz"));
        }

        TEST_METHOD(December08b_ApplyCommand_missingIf)
        {
            RegisterHandlerB test;
            Assert::AreEqual(false, test.ApplyCommand("qtzwui dec 4 zzz <= 15"));
            Assert::AreEqual(false, test.RegisterExists("qtzwui"));
        }

        TEST_METHOD(December08b_ApplyCommand_misspeltIf)
        {
            RegisterHandlerB test;
            Assert::AreEqual(false, test.ApplyCommand("test inc -2 iff abc > 0"));
            Assert::AreEqual(false, test.RegisterExists("test"));
        }

        TEST_METHOD(December08b_ApplyCommand_missingSpace)
        {
            RegisterHandlerB test;
            Assert::AreEqual(false, test.ApplyCommand("ab dec 20 if st==7"));
            Assert::AreEqual(false, test.RegisterExists("ab"));
        }

        TEST_METHOD(December08b_ApplyCommand_valid)
        {
            RegisterHandlerB test;
            Assert::AreEqual(true, test.ApplyCommand("abc dec 12"));
            Assert::AreEqual(true, test.ApplyCommand("testitest inc 9 if abc < 0"));
            Assert::AreEqual(true, test.RegisterExists("abc"));
            Assert::AreEqual(true, test.RegisterExists("testitest"));
            Assert::AreEqual(-12, test.GetValue("abc"));
            Assert::AreEqual(9, test.GetValue("testitest"));
        }

        // -----------------------------------
        // GetLargestRegisterValueEver
        // -----------------------------------
        TEST_METHOD(December08b_GetLargestRegisterValueEver_empty)
        {
            RegisterHandlerB test;
            Assert::AreEqual(INT_MIN, test.GetLargestRegisterValueEver());
        }

        TEST_METHOD(December08b_GetLargestRegisterValueEver_incNewValue)
        {
            RegisterHandlerB test;
            Assert::AreEqual(true, test.ApplyCommand("abcdef inc 17"));
            Assert::AreEqual(17, test.GetLargestRegisterValueEver());
        }

        TEST_METHOD(December08b_GetLargestRegisterValueEver_decNewValue)
        {
            RegisterHandlerB test;
            Assert::AreEqual(true, test.ApplyCommand("test inc -3"));
            Assert::AreEqual(-3, test.GetLargestRegisterValueEver());
        }

        TEST_METHOD(December08b_GetLargestRegisterValueEver_decOldValue)
        {
            RegisterHandlerB test;
            Assert::AreEqual(true, test.ApplyCommand("test inc 25"));
            Assert::AreEqual(true, test.ApplyCommand("test dec 4"));
            Assert::AreEqual(21, test.GetCurrentlyLargestRegisterValue());
            Assert::AreEqual(25, test.GetLargestRegisterValueEver());
        }

        // -----------------------------------
        // Advent of code sample data
        // -----------------------------------
        /*
        b inc 5 if a > 1
        a inc 1 if b < 5
        c dec -10 if a >= 1
        c inc -20 if c == 10

        For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).
        */
        TEST_METHOD(December08b_AoC_test)
        {
            RegisterHandlerB test;
            Assert::AreEqual(true, test.ApplyCommand("b inc 5 if a > 1"));
            Assert::AreEqual(true, test.ApplyCommand("a inc 1 if b < 5"));
            Assert::AreEqual(true, test.ApplyCommand("c dec -10 if a >= 1"));
            Assert::AreEqual(10, test.GetCurrentlyLargestRegisterValue());
            // one more command to reduce the currently highest value
            Assert::AreEqual(true, test.ApplyCommand("c inc -20 if c == 10"));
            Assert::AreEqual(1, test.GetCurrentlyLargestRegisterValue());
            Assert::AreEqual(10, test.GetLargestRegisterValueEver());
        }
    };
}
