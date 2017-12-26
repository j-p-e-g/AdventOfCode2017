#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December16.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December16;

    TEST_CLASS(Test_December16)
    {
    public:
        // ----------------------------------------
        // ParseLine
        // ----------------------------------------
        TEST_METHOD(December16_ParseLine_empty)
        {
            ProgramDancingMaster test(4);
            Assert::AreEqual(true, test.ParseLine(""));
            Assert::AreEqual("abcd", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_ParseLine_invalidCommand)
        {
            ProgramDancingMaster test(4);
            Assert::AreEqual(false, test.ParseLine("xyz"));
        }

        TEST_METHOD(December16_ParseLine_validSpin)
        {
            ProgramDancingMaster test(7);
            Assert::AreEqual(true, test.ParseLine("s5"));
            Assert::AreEqual("cdefgab", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_ParseLine_validExchange)
        {
            ProgramDancingMaster test(6);
            Assert::AreEqual(true, test.ParseLine("x0/4"));
            Assert::AreEqual("ebcdaf", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_ParseLine_validPartner)
        {
            ProgramDancingMaster test(5);
            Assert::AreEqual(true, test.ParseLine("pb/c"));
            Assert::AreEqual("acbde", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_ParseLine_validCommands)
        {
            ProgramDancingMaster test(12);
            Assert::AreEqual(true, test.ParseLine("pf/h,s10,x4/11"));
            Assert::AreEqual("cdehbfijklag", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_ParseLine_danglingComma)
        {
            ProgramDancingMaster test(26);
            Assert::AreEqual(false, test.ParseLine("x7/2,pc/l,"));
        }

        // ----------------------------------------
        // ApplySpin
        // ----------------------------------------
        TEST_METHOD(December16_ApplySpin_exceedsLength)
        {
            ProgramDancingMaster test(6);
            // exceeds size
            Assert::AreEqual(false, test.ApplySpin(7));
        }

        TEST_METHOD(December16_ApplySpin_zero)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplySpin(0));
        }

        TEST_METHOD(December16_ApplySpin_negative)
        {
            ProgramDancingMaster test(5);
            Assert::AreEqual(false, test.ApplySpin(-4));
        }

        TEST_METHOD(December16_ApplySpin_valid)
        {
            ProgramDancingMaster test(5);
            Assert::AreEqual(true, test.ApplySpin(3));
            Assert::AreEqual("cdeab", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_ApplySpin_length)
        {
            ProgramDancingMaster test(10);
            Assert::AreEqual(true, test.ApplySpin(10));
            // no change
            Assert::AreEqual("abcdefghij", test.GetFinalFormation().c_str());
        }

        // -----------------------------------
        // Parse Spin command
        // -----------------------------------
        TEST_METHOD(December16_ApplyDancingMove_spin_missingNumber)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("s"));
        }

        TEST_METHOD(December16_ApplyDancingMove_spin_notANumber)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("st2"));
        }

        TEST_METHOD(December16_ApplyDancingMove_spin_space)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("s 4"));
        }

        TEST_METHOD(December16_ApplyDancingMove_spin_zero)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("s0"));
        }

        TEST_METHOD(December16_ApplyDancingMove_spin_length)
        {
            ProgramDancingMaster test(5);
            // exceeds size
            Assert::AreEqual(false, test.ApplyDancingMove("s6"));
        }

        TEST_METHOD(December16_ApplyDancingMove_spin_valid)
        {
            ProgramDancingMaster test(16);
            Assert::AreEqual(true, test.ApplyDancingMove("s15"));
            Assert::AreEqual("bcdefghijklmnopa", test.GetFinalFormation().c_str());
        }

        // ----------------------------------------
        // ApplySwap
        // ----------------------------------------
        TEST_METHOD(December16_ApplySwap_ApplySwap_negativeIndex)
        {
            ProgramDancingMaster test(4);
            Assert::AreEqual(false, test.ApplySwap(-1, 2));
        }

        TEST_METHOD(December16_ApplySwap_ApplySwap_exceedsLength)
        {
            ProgramDancingMaster test(6);
            // exceeds size
            Assert::AreEqual(false, test.ApplySwap(3, 7));
        }

        TEST_METHOD(December16_ApplySwap_ApplySwap_self)
        {
            ProgramDancingMaster test(10);
            Assert::AreEqual(false, test.ApplySwap(5, 5));
        }

        TEST_METHOD(December16_ApplySwap_ApplySwap_valid)
        {
            ProgramDancingMaster test(5);
            Assert::AreEqual(true, test.ApplySwap(2, 4));
            Assert::AreEqual("abedc", test.GetFinalFormation().c_str());
        }

        // ----------------------------------------
        // Parse Exchange command
        // ----------------------------------------
        TEST_METHOD(December16_ApplyDancingMove_exchange_missingNumbers)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("x"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_lettersInsteadOfNumbers)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("xb/c"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_missingNumber1)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("x/3"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_missingNumber2)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("x7/"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_missingSeparator)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("x7 3"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_space)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("x 2/5"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_self)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("x3/3"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_unknownIndex1)
        {
            ProgramDancingMaster test(3);
            Assert::AreEqual(false, test.ApplyDancingMove("x5/2"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_unknownIndex2)
        {
            ProgramDancingMaster test(8);
            Assert::AreEqual(false, test.ApplyDancingMove("x7/10"));
        }

        TEST_METHOD(December16_ApplyDancingMove_exchange_valid)
        {
            ProgramDancingMaster test(5);
            Assert::AreEqual(true, test.ApplyDancingMove("x1/4"));
            Assert::AreEqual("aecdb", test.GetFinalFormation().c_str());
        }

        // ----------------------------------------
        // ApplyPartner
        // ----------------------------------------
        TEST_METHOD(December16_ApplySwap_ApplyPartner_self)
        {
            ProgramDancingMaster test(4);
            Assert::AreEqual(false, test.ApplyPartner('a', 'a'));
        }

        TEST_METHOD(December16_ApplySwap_ApplyPartner_invalidId1)
        {
            ProgramDancingMaster test(6);
            Assert::AreEqual(false, test.ApplyPartner('q', 'd'));
        }

        TEST_METHOD(December16_ApplySwap_ApplyPartner_invalidId2)
        {
            ProgramDancingMaster test(10);
            Assert::AreEqual(false, test.ApplyPartner('c', 'x'));
        }

        TEST_METHOD(December16_ApplySwap_ApplyPartner_valid)
        {
            ProgramDancingMaster test(8);
            Assert::AreEqual(true, test.ApplyPartner('d', 'e'));
            Assert::AreEqual("abcedfgh", test.GetFinalFormation().c_str());
        }

        // ----------------------------------------
        // Parse Partner command
        // ----------------------------------------

        TEST_METHOD(December16_ApplyDancingMove_partner_missingIds)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("p"));
        }

        TEST_METHOD(December16_ApplyDancingMove_partner_numbersInsteadOfLetters)
        {
            ProgramDancingMaster test;
            Assert::AreEqual(false, test.ApplyDancingMove("p2/5"));
        }

        TEST_METHOD(December16_ApplyDancingMove_partner_missingId1)
        {
            ProgramDancingMaster test(6);
            Assert::AreEqual(false, test.ApplyDancingMove("p/d"));
        }

        TEST_METHOD(December16_ApplyDancingMove_partner_missingId2)
        {
            ProgramDancingMaster test(3);
            Assert::AreEqual(false, test.ApplyDancingMove("pa/"));
        }

        TEST_METHOD(December16_ApplyDancingMove_partner_missingSeparator)
        {
            ProgramDancingMaster test(10);
            Assert::AreEqual(false, test.ApplyDancingMove("pdf"));
        }

        TEST_METHOD(December16_ApplyDancingMove_partner_space)
        {
            ProgramDancingMaster test(3);
            Assert::AreEqual(false, test.ApplyDancingMove("p a/b"));
        }

        TEST_METHOD(December16_ApplyDancingMove_partner_invalidIndex)
        {
            ProgramDancingMaster test(3);
            Assert::AreEqual(false, test.ApplyDancingMove("pc/n"));
        }

        TEST_METHOD(December16_ApplyDancingMove_partner_valid)
        {
            ProgramDancingMaster test(6);
            Assert::AreEqual(true, test.ApplyDancingMove("pb/f"));
            Assert::AreEqual("afcdeb", test.GetFinalFormation().c_str());
        }

        // ----------------------------------------
        // GetFinalFormation
        // ----------------------------------------
        TEST_METHOD(December16_GetFinalFormation_unchanged)
        {
            ProgramDancingMaster test(7);
            Assert::AreEqual("abcdefg", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_spin1)
        {
            ProgramDancingMaster test(4);
            test.ApplySpin(1);
            Assert::AreEqual("dabc", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_spin3)
        {
            ProgramDancingMaster test(8);
            test.ApplySpin(3);
            Assert::AreEqual("fghabcde", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_spinComplete)
        {
            ProgramDancingMaster test(5);
            test.ApplySpin(5);
            // no effect
            Assert::AreEqual("abcde", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_spinDouble)
        {
            ProgramDancingMaster test(4);
            test.ApplySpin(2);
            Assert::AreEqual("cdab", test.GetFinalFormation().c_str());
            // return to initial formation
            test.ApplySpin(2);
            Assert::AreEqual("abcd", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_exchange)
        {
            ProgramDancingMaster test(4);
            test.ApplyDancingMove("x2/1");
            Assert::AreEqual("acbd", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_exchangeDouble)
        {
            ProgramDancingMaster test(11);
            test.ApplyDancingMove("x5/8");
            Assert::AreEqual("abcdeighfjk", test.GetFinalFormation().c_str());
            // return to initial formation
            test.ApplyDancingMove("x5/8");
            Assert::AreEqual("abcdefghijk", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_partner)
        {
            ProgramDancingMaster test(4);
            test.ApplyDancingMove("pb/d");
            Assert::AreEqual("adcb", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_partnerDouble)
        {
            ProgramDancingMaster test(5);
            test.ApplyDancingMove("pc/a");
            Assert::AreEqual("cbade", test.GetFinalFormation().c_str());
            // return to initial formation
            test.ApplyDancingMove("pa/c");
            Assert::AreEqual("abcde", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_severalMoves)
        {
            ProgramDancingMaster test(3);
            test.ApplyDancingMove("x1/0");
            Assert::AreEqual("bac", test.GetFinalFormation().c_str());
            test.ApplyDancingMove("pb/c");
            Assert::AreEqual("cab", test.GetFinalFormation().c_str());
            // return to initial formation
            test.ApplyDancingMove("s2");
            Assert::AreEqual("abc", test.GetFinalFormation().c_str());
        }

        /*
        For example, with only five programs standing in a line (abcde), they could do the following dance:

        s1, a spin of size 1: eabcd.
        x3/4, swapping the last two programs: eabdc.
        pe/b, swapping programs e and b: baedc.

        After finishing their dance, the programs end up in order baedc.
        */
        TEST_METHOD(December16_GetFinalFormation_AoC_test)
        {
            ProgramDancingMaster test(5);
            test.ApplyDancingMove("s1");
            test.ApplyDancingMove("x3/4");
            test.ApplyDancingMove("pe/b");
            Assert::AreEqual("baedc", test.GetFinalFormation().c_str());
        }
    };
}
