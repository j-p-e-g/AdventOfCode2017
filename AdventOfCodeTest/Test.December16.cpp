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
        // Spin: ApplyMove
        // ----------------------------------------
        TEST_METHOD(December16_Spin_ApplyMove_exceedsLength)
        {
            // exceeds size
            std::string formation = "abcdef";
            Spin move(7);
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Spin_ApplyMove_zero)
        {
            std::string formation = "abc";
            Spin move(0);
            Assert::AreEqual(false, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Spin_ApplyMove_negative)
        {
            std::string formation = "abcd";
            Spin move(-4);
            Assert::AreEqual(false, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Spin_ApplyMove_valid)
        {
            std::string formation = "abcde";
            Spin move(3);
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(true, move.ApplyMove(formation));
            Assert::AreEqual("cdeab", formation.c_str());
        }

        TEST_METHOD(December16_Spin_ApplyMove_length)
        {
            std::string formation = "abcdefghij";
            Spin move(10);
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(true, move.ApplyMove(formation));
            // no change
            Assert::AreEqual("abcdefghij", formation.c_str());
        }

        // -----------------------------------
        // ParseDancingMove: general
        // -----------------------------------
        TEST_METHOD(December16_ParseDancingMove_invalidCommand)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("xyz", move));
        }

        // -----------------------------------
        // Parse Spin command
        // -----------------------------------
        TEST_METHOD(December16_ParseDancingMove_spin_missingNumber)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("s", move));
        }

        TEST_METHOD(December16_ParseDancingMove_spin_notANumber)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("st2", move));
        }

        TEST_METHOD(December16_ParseDancingMove_spin_space)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("s 4", move));
        }

        TEST_METHOD(December16_ParseDancingMove_spin_zero)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("s0", move));
        }

        TEST_METHOD(December16_ParseDancingMove_spin_length)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(true, test.ParseDancingMove("s6", move));
            Assert::AreEqual(true, move->IsValid());

            // exceeds size
            std::string formation = "abcde";
            Assert::AreEqual(false, move->ApplyMove(formation));
        }

        TEST_METHOD(December16_ParseDancingMove_spin_valid)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(true, test.ParseDancingMove("s15", move));

            std::string formation = "abcdefghijklmnop";
            Assert::AreEqual(true, move->IsValid());
            Assert::AreEqual(true, move->ApplyMove(formation));
            Assert::AreEqual("bcdefghijklmnopa", formation.c_str());
        }

        // ----------------------------------------
        // Exchange: ApplyMove
        // ----------------------------------------
        TEST_METHOD(December16_Exchange_ApplyMove_negativeIndex)
        {
            ProgramDancingMaster test(4);
            Exchange swap(-1, 2);
            Assert::AreEqual(false, swap.IsValid());
        }

        TEST_METHOD(December16_Exchange_ApplyMove_exceedsLength)
        {
            // exceeds size
            std::string formation = "abcdef";
            Exchange move(3,7);
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Exchange_ApplyMove_self)
        {
            std::string formation = "abcdefghijkl";
            Exchange move(5, 5);
            Assert::AreEqual(false, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Exchange_ApplyMove_valid)
        {
            std::string formation = "abcde";
            Exchange move(2, 4);
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(true, move.ApplyMove(formation));
            Assert::AreEqual("abedc", formation.c_str());
        }

        TEST_METHOD(December16_Exchange_CanUndo_true)
        {
            Exchange swapA(4, 7);
            Exchange swapB(4, 7);
            Exchange swapC(7, 4);

            Assert::AreEqual(true, swapA.CanUndo(std::make_shared<Exchange>(swapB)));
            Assert::AreEqual(true, swapC.CanUndo(std::make_shared<Exchange>(swapB)));
        }

        TEST_METHOD(December16_Exchange_CanUndo_false)
        {
            Exchange swapA(3, 1);
            Exchange swapB(5, 1);
            Exchange swapC(3, 2);

            Assert::AreEqual(false, swapA.CanUndo(std::make_shared<Exchange>(swapB)));
            Assert::AreEqual(false, swapA.CanUndo(std::make_shared<Exchange>(swapC)));
        }

        TEST_METHOD(December16_Exchange_AffectsSameTarget)
        {
            Exchange swapA(4, 7);
            Exchange swapB(7, 6);
            Exchange swapC(4, 14);
            Exchange swapD(8, 3);

            Assert::AreEqual(true, swapA.AffectsSameTarget(std::make_shared<Exchange>(swapB)));
            Assert::AreEqual(true, swapA.AffectsSameTarget(std::make_shared<Exchange>(swapC)));
            Assert::AreEqual(false, swapA.AffectsSameTarget(std::make_shared<Exchange>(swapD)));
        }

        // ----------------------------------------
        // Parse Exchange command
        // ----------------------------------------
        TEST_METHOD(December16_ParseDancingMove_exchange_missingNumbers)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("x", move));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_lettersInsteadOfNumbers)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("xb/c", move));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_missingNumber1)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("x/3", move));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_missingNumber2)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("x7/", move));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_missingSeparator)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("x7 3", move));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_space)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("x 2/5", move));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_self)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("x3/3", move));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_unknownIndex1)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(true, test.ParseDancingMove("x5/2", move));
            Assert::AreEqual(true, move->IsValid());

            std::string formation = "abc";
            Assert::AreEqual(false, move->ApplyMove(formation));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_unknownIndex2)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(true, test.ParseDancingMove("x7/10", move));
            Assert::AreEqual(true, move->IsValid());

            std::string formation = "abcdefgh";
            Assert::AreEqual(false, move->ApplyMove(formation));
        }

        TEST_METHOD(December16_ParseDancingMove_exchange_valid)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(true, test.ParseDancingMove("x1/4", move));
            Assert::AreEqual(true, move->IsValid());

            std::string formation = "abcde";
            Assert::AreEqual(true, move->ApplyMove(formation));
        }

        // ----------------------------------------
        // Partner: ApplyMove
        // ----------------------------------------
        TEST_METHOD(December16_Partner_ApplyMove_self)
        {
            std::string formation = "abcd";
            Partner move('a', 'a');
            Assert::AreEqual(false, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Partner_ApplyMove_invalidId1)
        {
            std::string formation = "abcdefghijkl";
            Partner move('q', 'd');
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Partner_ApplyMove_invalidId2)
        {
            std::string formation = "abcdefghij";
            Partner move('c', 'x');
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(false, move.ApplyMove(formation));
        }

        TEST_METHOD(December16_Partner_ApplyMove_valid)
        {
            std::string formation = "abcdefgh";
            Partner move('d', 'e');
            Assert::AreEqual(true, move.IsValid());
            Assert::AreEqual(true, move.ApplyMove(formation));
            Assert::AreEqual("abcedfgh", formation.c_str());
        }

        TEST_METHOD(December16_Partner_CanUndo_true)
        {
            Partner moveA('c', 'd');
            Partner moveB('c', 'd');
            Partner moveC('d', 'c');

            Assert::AreEqual(true, moveA.CanUndo(std::make_shared<Partner>(moveB)));
            Assert::AreEqual(true, moveC.CanUndo(std::make_shared<Partner>(moveA)));
        }

        TEST_METHOD(December16_Partner_CanUndo_false)
        {
            Partner moveA('b', 'f');
            Partner moveB('b', 'g');
            Partner moveC('a', 'f');

            Assert::AreEqual(false, moveA.CanUndo(std::make_shared<Partner>(moveB)));
            Assert::AreEqual(false, moveA.CanUndo(std::make_shared<Partner>(moveC)));
        }

        TEST_METHOD(December16_Partner_AffectsSameTarget)
        {
            Partner moveA('b', 'f');
            Partner moveB('g', 'f');
            Partner moveC('g', 'b');
            Partner moveD('e', 'c');

            Assert::AreEqual(true, moveA.AffectsSameTarget(std::make_shared<Partner>(moveB)));
            Assert::AreEqual(true, moveA.AffectsSameTarget(std::make_shared<Partner>(moveC)));
            Assert::AreEqual(false, moveA.AffectsSameTarget(std::make_shared<Partner>(moveD)));
        }

        // ----------------------------------------
        // Parse Partner command
        // ----------------------------------------

        TEST_METHOD(December16_ParseDancingMove_partner_missingIds)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("p", move));
        }

        TEST_METHOD(December16_ParseDancingMove_partner_numbersInsteadOfLetters)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("p2/5", move));
        }

        TEST_METHOD(December16_ParseDancingMove_partner_missingId1)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("p/d", move));
        }

        TEST_METHOD(December16_ParseDancingMove_partner_missingId2)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("pa/", move));
        }

        TEST_METHOD(December16_ParseDancingMove_partner_missingSeparator)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("pdf", move));
        }

        TEST_METHOD(December16_ParseDancingMove_partner_space)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(false, test.ParseDancingMove("p a/b", move));
        }

        TEST_METHOD(December16_ParseDancingMove_partner_invalidIndex)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(true, test.ParseDancingMove("pc/n", move));
            Assert::AreEqual(true, move->IsValid());

            std::string formation = "abc";
            Assert::AreEqual(false, move->ApplyMove(formation));
        }

        TEST_METHOD(December16_ParseDancingMove_partner_valid)
        {
            ProgramDancingMaster test;
            std::shared_ptr<DancingMove> move;
            Assert::AreEqual(true, test.ParseDancingMove("pb/f", move));
            Assert::AreEqual(true, move->IsValid());

            std::string formation = "abcdef";
            Assert::AreEqual(true, move->ApplyMove(formation));
            Assert::AreEqual("afcdeb", formation.c_str());
        }

        // ----------------------------------------
        // ParseLine/GetFinalFormation
        // ----------------------------------------
        TEST_METHOD(December16_GetFinalFormation_unchanged)
        {
            ProgramDancingMaster test(7);
            Assert::AreEqual("abcdefg", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_ParseLine_empty)
        {
            ProgramDancingMaster test(4);
            Assert::AreEqual(true, test.ParseLine(""));
            Assert::AreEqual("abcd", test.GetFinalFormation().c_str());
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

        TEST_METHOD(December16_ParseLine_danglingComma)
        {
            ProgramDancingMaster test(26);
            Assert::AreEqual(false, test.ParseLine("x7/2,pc/l,"));
        }

        TEST_METHOD(December16_ParseLine_validCommands)
        {
            ProgramDancingMaster test(12);
            Assert::AreEqual(true, test.ParseLine("pf/h,s10,x4/11"));
            Assert::AreEqual("cdehbfijklag", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_spinDouble)
        {
            ProgramDancingMaster test(4);
            Assert::AreEqual(true, test.ParseLine("s2,s2"));
            // return to initial formation
            Assert::AreEqual("abcd", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_exchangeDouble)
        {
            ProgramDancingMaster test(11);
            Assert::AreEqual(true, test.ParseLine("x5/8,x5/8"));
            // return to initial formation
            Assert::AreEqual("abcdefghijk", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16_GetFinalFormation_partnerDouble)
        {
            ProgramDancingMaster test(5);
            Assert::AreEqual(true, test.ParseLine("pc/a,pa/c"));
            // return to initial formation
            Assert::AreEqual("abcde", test.GetFinalFormation().c_str());
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
            Assert::AreEqual(true, test.ParseLine("s1,x3/4,pe/b"));
            Assert::AreEqual("baedc", test.GetFinalFormation().c_str());
        }
    };
}
