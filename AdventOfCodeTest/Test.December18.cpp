#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December18.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December18;

    TEST_CLASS(Test_December18)
    {
    public:
        
        // ------------------------------
        // CharOrNumber
        // ------------------------------
        TEST_METHOD(December18_CharOrNumber_empty)
        {
            CharOrNumber test("");
            Assert::AreEqual(false, test.isValid);
            Assert::AreEqual(false, test.isChar);
        }

        TEST_METHOD(December18_CharOrNumber_number)
        {
            CharOrNumber test("7902");
            Assert::AreEqual(true, test.isValid);
            Assert::AreEqual(false, test.isChar);
            Assert::AreEqual(7902, test.value);
        }

        TEST_METHOD(December18_CharOrNumber_letter)
        {
            CharOrNumber test("p");
            Assert::AreEqual(true, test.isValid);
            Assert::AreEqual(true, test.isChar);
            Assert::AreEqual('p', test.id);
        }

        TEST_METHOD(December18_CharOrNumber_otherChar)
        {
            CharOrNumber test("*");
            Assert::AreEqual(false, test.isValid);
            Assert::AreEqual(false, test.isChar);
        }

        TEST_METHOD(December18_CharOrNumber_string)
        {
            CharOrNumber test("17z");
            Assert::AreEqual(false, test.isValid);
            Assert::AreEqual(false, test.isChar);
        }

        // ------------------------------
        // RegisterSolo::ParseLine
        // ------------------------------
        TEST_METHOD(December18_ParseLine_empty)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine(""));
        }

        TEST_METHOD(December18_ParseLine_unknownCommand)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("foo c 8"));
        }

        TEST_METHOD(December18_ParseLine_multiCharRegister1)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("add xy 5"));
        }

        TEST_METHOD(December18_ParseLine_multiCharRegister2)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("set k rr"));
        }

        TEST_METHOD(December18_ParseLine_numberRegister)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("set 3 z"));
        }

        TEST_METHOD(December18_ParseLine_invalidSnd_2ndValue)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("snd k 5"));
        }

        TEST_METHOD(December18_ParseLine_validSndNumber)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("snd 28"));
        }

        TEST_METHOD(December18_ParseLine_validSndChar)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("snd y"));
        }

        TEST_METHOD(December18_ParseLine_invalidSet_3rdValue)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("set q 51 b"));
        }

        TEST_METHOD(December18_ParseLine_validSetNumber)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("set f 25"));
        }

        TEST_METHOD(December18_ParseLine_validSetChar)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("set b k"));
        }

        TEST_METHOD(December18_ParseLine_validAddNumber)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("add q -2"));
        }

        TEST_METHOD(December18_ParseLine_validAddChar)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("add z z"));
        }

        TEST_METHOD(December18_ParseLine_validMulNumber)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("mul d -1"));
        }

        TEST_METHOD(December18_ParseLine_validMulChar)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("mul c b"));
        }

        TEST_METHOD(December18_ParseLine_invalidMod_zero)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("mod g 0"));
        }

        TEST_METHOD(December18_ParseLine_invalidMod_negative)
        {
            RegisterSolo test;
            Assert::AreEqual(false, test.ParseLine("mod t -4"));
        }

        TEST_METHOD(December18_ParseLine_validModNumber)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("mod r 93"));
        }

        TEST_METHOD(December18_ParseLine_validModChar)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("mod k a"));
        }

        TEST_METHOD(December18_ParseLine_validJgzNumber)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("jgz d -5"));
        }

        TEST_METHOD(December18_ParseLine_validJgzChar)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("jgz e r"));
        }

        TEST_METHOD(December18_ParseLine_validRcvNumber)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("rcv 0"));
        }

        TEST_METHOD(December18_ParseLine_validRcvChar)
        {
            RegisterSolo test;
            Assert::AreEqual(true, test.ParseLine("rcv d"));
        }

        // ------------------------------------------
        // Apply commands: general
        // ------------------------------------------
        TEST_METHOD(December18_RegisterSolo_noCommands)
        {
            RegisterSolo test;
            Assert::AreEqual(-1, test.GetCurrentIndex());
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
            // default value for all registers
            Assert::AreEqual(0, static_cast<int>(test.GetRegisterValue('x')));
        }

        // ------------------------------------------
        // Apply commands: RegisterSet
        // ------------------------------------------
        TEST_METHOD(December18_RegisterSet_Apply_nonExisting)
        {
            RegisterSolo test;
            test.SetCurrentIndex(5);

            RegisterSet command(CharOrNumber("a"), CharOrNumber("9765"));
            command.Apply(test);
            Assert::AreEqual(6, test.GetCurrentIndex());

            Assert::AreEqual(9765, static_cast<int>(test.GetRegisterValue('a')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterSet_Apply)
        {
            RegisterSolo test;
            test.SetCurrentIndex(1);

            test.SetRegisterValue('r', -3);
            test.SetRegisterValue('w', 100);
            Assert::AreEqual(-3, static_cast<int>(test.GetRegisterValue('r')));
            Assert::AreEqual(100, static_cast<int>(test.GetRegisterValue('w')));

            RegisterSet command(CharOrNumber("w"), CharOrNumber("r"));
            command.Apply(test);
            Assert::AreEqual(2, test.GetCurrentIndex());

            Assert::AreEqual(-3, static_cast<int>(test.GetRegisterValue('r')));
            Assert::AreEqual(-3, static_cast<int>(test.GetRegisterValue('w')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        // ------------------------------------------
        // Apply commands: RegisterAdd
        // ------------------------------------------
        TEST_METHOD(December18_RegisterAdd_Apply_nonExisting)
        {
            RegisterSolo test;
            test.SetCurrentIndex(17);

            RegisterAdd command(CharOrNumber("z"), CharOrNumber("50"));
            command.Apply(test);
            Assert::AreEqual(18, test.GetCurrentIndex());

            Assert::AreEqual(50, static_cast<int>(test.GetRegisterValue('z')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterAdd_Apply_negative)
        {
            RegisterSolo test;
            test.SetRegisterValue('q', 13);
            test.SetCurrentIndex(32);

            RegisterAdd command(CharOrNumber("q"), CharOrNumber("-5"));
            command.Apply(test);
            Assert::AreEqual(33, test.GetCurrentIndex());

            Assert::AreEqual(8, static_cast<int>(test.GetRegisterValue('q')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterAdd_Apply_self)
        {
            RegisterSolo test;
            test.SetRegisterValue('b', 73);
            test.SetCurrentIndex(4);

            RegisterAdd command(CharOrNumber("b"), CharOrNumber("b"));
            command.Apply(test);
            Assert::AreEqual(5, test.GetCurrentIndex());

            Assert::AreEqual(146, static_cast<int>(test.GetRegisterValue('b')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        // ------------------------------------------
        // Apply commands: RegisterMul
        // ------------------------------------------
        TEST_METHOD(December18_RegisterMul_Apply_nonExisting)
        {
            RegisterSolo test;
            test.SetCurrentIndex(3000);

            RegisterMul command(CharOrNumber("g"), CharOrNumber("723"));
            command.Apply(test);
            Assert::AreEqual(3001, test.GetCurrentIndex());

            // multiplied with 0
            Assert::AreEqual(0, static_cast<int>(test.GetRegisterValue('g')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterMul_Apply_self)
        {
            RegisterSolo test;
            test.SetRegisterValue('f', 5);
            test.SetCurrentIndex(2);

            RegisterMul command(CharOrNumber("f"), CharOrNumber("f"));
            command.Apply(test);
            Assert::AreEqual(3, test.GetCurrentIndex());

            // square
            Assert::AreEqual(25, static_cast<int>(test.GetRegisterValue('f')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterMul_Apply_negative)
        {
            RegisterSolo test;
            test.SetRegisterValue('s', -27);
            test.SetRegisterValue('t', 10);
            test.SetCurrentIndex(99);

            RegisterMul command(CharOrNumber("t"), CharOrNumber("s"));
            command.Apply(test);
            Assert::AreEqual(100, test.GetCurrentIndex());

            Assert::AreEqual(-27, static_cast<int>(test.GetRegisterValue('s')));
            Assert::AreEqual(-270, static_cast<int>(test.GetRegisterValue('t')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        // ------------------------------------------
        // Apply commands: RegisterMod
        // ------------------------------------------
        TEST_METHOD(December18_RegisterMod_Apply_nonExisting)
        {
            RegisterSolo test;
            test.SetCurrentIndex(21);

            RegisterMod command(CharOrNumber("x"), CharOrNumber("70"));
            command.Apply(test);
            Assert::AreEqual(22, test.GetCurrentIndex());

            // 0 % 70
            Assert::AreEqual(0, static_cast<int>(test.GetRegisterValue('x')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterMod_Apply)
        {
            RegisterSolo test;
            test.SetCurrentIndex(3);
            test.SetRegisterValue('u', 98);

            RegisterMod command(CharOrNumber("u"), CharOrNumber("9"));
            command.Apply(test);
            Assert::AreEqual(4, test.GetCurrentIndex());

            Assert::AreEqual(8, static_cast<int>(test.GetRegisterValue('u')));
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        // ------------------------------------------
        // Apply commands: RegisterSnd
        // ------------------------------------------
        TEST_METHOD(December18_RegisterSnd_Apply)
        {
            RegisterSolo test;
            test.SetCurrentIndex(0);
            test.SetFrequency(25);
            test.SetRecoveredFrequency(25);
            Assert::AreEqual(25, static_cast<int>(test.GetFrequency()));

            RegisterSnd command(CharOrNumber("18"));
            command.Apply(test);
            Assert::AreEqual(1, test.GetCurrentIndex());

            Assert::AreEqual(18, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(25, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterSnd_Apply_nonExisting)
        {
            RegisterSolo test;
            test.SetCurrentIndex(25);

            RegisterSnd command(CharOrNumber("i"));
            command.Apply(test);
            Assert::AreEqual(26, test.GetCurrentIndex());

            Assert::AreEqual(0, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        // ------------------------------------------
        // Apply commands: RegisterRcv
        // ------------------------------------------
        TEST_METHOD(December18_RegisterRcv_Apply_noSound)
        {
            RegisterSolo test;
            test.SetCurrentIndex(8);

            RegisterRcv command(CharOrNumber("2"));
            command.Apply(test);
            Assert::AreEqual(9, test.GetCurrentIndex());

            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterRcv_Apply)
        {
            RegisterSolo test;
            test.SetCurrentIndex(71);
            test.SetRegisterValue('a', -9);

            RegisterSnd snd(CharOrNumber("55"));
            snd.Apply(test);
            Assert::AreEqual(72, test.GetCurrentIndex());

            RegisterRcv command(CharOrNumber("a"));
            command.Apply(test);
            Assert::AreEqual(73, test.GetCurrentIndex());

            Assert::AreEqual(55, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(55, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterRcv_Apply_skip)
        {
            RegisterSolo test;
            test.SetCurrentIndex(402);

            RegisterSnd snd(CharOrNumber("27"));
            snd.Apply(test);
            Assert::AreEqual(403, test.GetCurrentIndex());

            RegisterRcv command(CharOrNumber("a"));
            command.Apply(test);
            Assert::AreEqual(404, test.GetCurrentIndex());

            Assert::AreEqual(27, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterRcv_Apply_repeat)
        {
            RegisterSolo test;
            test.SetCurrentIndex(67);
            test.SetRecoveredFrequency(93);

            RegisterSnd snd(CharOrNumber("444"));
            snd.Apply(test);
            Assert::AreEqual(68, test.GetCurrentIndex());
            Assert::AreEqual(444, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(93, static_cast<int>(test.GetRecoveredFrequency()));

            RegisterRcv command(CharOrNumber("-2"));
            command.Apply(test);
            Assert::AreEqual(69, test.GetCurrentIndex());

            Assert::AreEqual(444, static_cast<int>(test.GetRecoveredFrequency()));
        }

        // ------------------------------------------
        // Apply commands: RegisterJgz
        // ------------------------------------------
        TEST_METHOD(December18_RegisterJgz_Apply_skipNonExisting)
        {
            RegisterSolo test;
            test.SetCurrentIndex(123);

            RegisterJgz command(CharOrNumber("b"), CharOrNumber("98"));
            command.Apply(test);
            Assert::AreEqual(124, test.GetCurrentIndex());

            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterJgz_Apply_skipNegative)
        {
            RegisterSolo test;
            test.SetCurrentIndex(53);
            test.SetRegisterValue('q', -2);

            RegisterJgz command(CharOrNumber("q"), CharOrNumber("-30"));
            command.Apply(test);

            Assert::AreEqual(54, test.GetCurrentIndex());
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_RegisterJgz_Apply)
        {
            RegisterSolo test;
            test.SetCurrentIndex(12);

            RegisterJgz command(CharOrNumber("17"), CharOrNumber("-3"));
            command.Apply(test);

            Assert::AreEqual(9, test.GetCurrentIndex());
            Assert::AreEqual(-1, static_cast<int>(test.GetFrequency()));
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        // ------------------------------------------
        // RegisterSolo::GetRecoveredFrequency
        // ------------------------------------------
        TEST_METHOD(December18_GetRecoveredFrequency_empty)
        {
            RegisterSolo test;
            test.ExecuteCommands();
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_GetRecoveredFrequency_invalid_immediate)
        {
            RegisterSolo test;
            // skipped, c is zero
            test.ParseLine("rcv c");
            test.ExecuteCommands();

            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_GetRecoveredFrequency_invalid_valueZero)
        {
            RegisterSolo test;
            test.ParseLine("snd 15");
            // skipped, d is zero
            test.ParseLine("rcv d");
            test.ExecuteCommands();

            // we played a sound but d is zero
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_GetRecoveredFrequency_invalid_noSound)
        {
            RegisterSolo test;
            test.ParseLine("set x 5");
            // not skipped, x is non-zero
            test.ParseLine("rcv x");
            test.ExecuteCommands();

            // x is non-zero but there's nothing to recover
            Assert::AreEqual(-1, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_GetRecoveredFrequency_valid_zero)
        {
            RegisterSolo test;
            // f is zero
            test.ParseLine("snd f");
            test.ParseLine("add f 3");
            // not skipped, f is non-zero
            test.ParseLine("rcv f");
            test.ExecuteCommands();

            // the last sound was played with a frequency of 0
            Assert::AreEqual(0, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_GetRecoveredFrequency_valid_nonZero)
        {
            RegisterSolo test;
            test.ParseLine("set k 743");
            test.ParseLine("snd 16");
            // not skipped, k is non-zero
            test.ParseLine("rcv k");
            test.ExecuteCommands();

            Assert::AreEqual(16, static_cast<int>(test.GetRecoveredFrequency()));
        }

        TEST_METHOD(December18_GetRecoveredFrequency_multipleRecoveries)
        {
            RegisterSolo test;
            test.ParseLine("set a 2");
            test.ParseLine("snd a");
            // skipped, b is zero
            test.ParseLine("rcv b");
            test.ParseLine("snd 84");
            // not skipped, a is non-zero
            test.ParseLine("rcv a");
            test.ParseLine("snd a");
            // valid recovery, but not the first recovered frequency
            test.ParseLine("rcv a");
            test.ExecuteCommands();

            Assert::AreEqual(84, static_cast<int>(test.GetRecoveredFrequency()));
        }

        /*
        set a 1
        add a 2
        mul a a
        mod a 5
        snd a
        set a 0
        rcv a
        jgz a -1
        set a 1
        jgz a -2

        At the time the recover operation is executed, the frequency of the last sound played is 4.
        */
        TEST_METHOD(December18_GetRecoveredFrequency_AoC_test)
        {
            RegisterSolo test;
            test.ParseLine("set a 1");
            test.ParseLine("add a 2");
            test.ParseLine("mul a a");
            test.ParseLine("mod a 5");
            test.ParseLine("snd a");
            test.ParseLine("set a 0");
            test.ParseLine("rcv a");
            test.ParseLine("jgz a -1");
            test.ParseLine("set a 1");
            test.ParseLine("jgz a -2");
            test.ExecuteCommands();

            Assert::AreEqual(4, static_cast<int>(test.GetRecoveredFrequency()));
        }
    };
}
