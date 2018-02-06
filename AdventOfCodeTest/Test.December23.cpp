#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December23.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December18;
    using namespace AdventOfCode::December23;

    TEST_CLASS(Test_December23)
    {
    public:
        TEST_METHOD(December23_ParseLine_validSet)
        {
            RegisterHandler test;
            Assert::AreEqual(true, test.ParseLine("set d -463"));
        }

        TEST_METHOD(December23_ParseLine_validSub)
        {
            RegisterHandler test;
            Assert::AreEqual(true, test.ParseLine("sub a f"));
        }

        TEST_METHOD(December23_ParseLine_validMul)
        {
            RegisterHandler test;
            Assert::AreEqual(true, test.ParseLine("mul d 4"));
        }

        TEST_METHOD(December23_ParseLine_validJnz)
        {
            RegisterHandler test;
            Assert::AreEqual(true, test.ParseLine("jnz b 8"));
        }

        TEST_METHOD(December23_ParseLine_invalidAdd)
        {
            RegisterHandler test;
            Assert::AreEqual(false, test.ParseLine("add f 3"));
        }

        TEST_METHOD(December23_ParseLine_invalidSnd)
        {
            RegisterHandler test;
            Assert::AreEqual(false, test.ParseLine("snd b 64"));
        }

        TEST_METHOD(December23_ParseLine_invalidRcv)
        {
            RegisterHandler test;
            Assert::AreEqual(false, test.ParseLine("rcv b g"));
        }

        TEST_METHOD(December23_ParseLine_invalidMod)
        {
            RegisterHandler test;
            Assert::AreEqual(false, test.ParseLine("mod c 2"));
        }

        TEST_METHOD(December23_RegisterSub_Apply)
        {
            RegisterHandler test;
            test.SetCurrentIndex(0);

            RegisterSub command(CharOrNumber("b"), CharOrNumber("14"));
            command.Apply(test);
            Assert::AreEqual(1, test.GetCurrentIndex());

            Assert::AreEqual(-14, static_cast<int>(test.GetRegisterValue('b')));
        }

        TEST_METHOD(December23_RegisterJnz_dontSkip)
        {
            RegisterHandler test;
            // d is zero, so don't execute the skip
            Assert::AreEqual(true, test.ParseLine("jnz d 2"));
            Assert::AreEqual(true, test.ParseLine("set f 19"));
            test.ExecuteCommands();

            Assert::AreEqual(0, static_cast<int>(test.GetRegisterValue('d')));
            Assert::AreEqual(19, static_cast<int>(test.GetRegisterValue('f')));
        }

        TEST_METHOD(December23_RegisterJnz_skip)
        {
            RegisterHandler test;
            Assert::AreEqual(true, test.ParseLine("set d 36"));
            Assert::AreEqual(true, test.ParseLine("jnz d 2"));
            Assert::AreEqual(true, test.ParseLine("set e 3"));
            test.ExecuteCommands();

            Assert::AreEqual(36, static_cast<int>(test.GetRegisterValue('d')));
            Assert::AreEqual(0, static_cast<int>(test.GetRegisterValue('e')));
        }

        TEST_METHOD(December23_GetMultiplierCommandCount_skippedMul)
        {
            RegisterHandler test;
            Assert::AreEqual(true, test.ParseLine("set c 3"));
            Assert::AreEqual(true, test.ParseLine("jnz c 3"));
            Assert::AreEqual(true, test.ParseLine("mul c -1"));
            Assert::AreEqual(true, test.ParseLine("mul c c"));
            Assert::AreEqual(true, test.ParseLine("set a -15"));
            Assert::AreEqual(true, test.ParseLine("set b 2"));
            test.ExecuteCommands();
            Assert::AreEqual(0, test.GetMultiplierCommandCount());
        }

        TEST_METHOD(December23_GetMultiplierCommandCount)
        {
            RegisterHandler test;
            Assert::AreEqual(true, test.ParseLine("jnz d 2"));
            Assert::AreEqual(true, test.ParseLine("mul e 3"));
            Assert::AreEqual(true, test.ParseLine("sub d 3"));
            Assert::AreEqual(true, test.ParseLine("mul b b"));
            test.ExecuteCommands();
            Assert::AreEqual(2, test.GetMultiplierCommandCount());
        }
    };
}
