#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December16b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December16;

    TEST_CLASS(Test_December16b)
    {
    public:
        TEST_METHOD(December16b_RepeatedDance_spin)
        {
            ProgramDancingMasterB test(5, 3);
            test.ParseLine("s2");
            Assert::AreEqual("eabcd", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16b_RepeatedDance_exchange_even)
        {
            ProgramDancingMasterB test(7, 4);
            test.ParseLine("x3/5");
            // cancel each other out
            Assert::AreEqual("abcdefg", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16b_RepeatedDance_exchange_odd)
        {
            ProgramDancingMasterB test(3, 21);
            test.ParseLine("x1/0");
            Assert::AreEqual("bac", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16b_RepeatedDance_partner_even)
        {
            ProgramDancingMasterB test(4, 42);
            test.ParseLine("pb/c");
            // cancel each other out
            Assert::AreEqual("abcd", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16b_RepeatedDance_partner_odd)
        {
            ProgramDancingMasterB test(5, 9);
            test.ParseLine("pd/e");
            Assert::AreEqual("abced", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16b_RepeatedDance_once)
        {
            ProgramDancingMasterB test(8, 1);
            test.ParseLine("s5,x5/7,pb/a");
            Assert::AreEqual("defghcab", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16b_RepeatedDance_repeats)
        {
            ProgramDancingMasterB test(6, 3);
            test.ParseLine("pc/e,s4,x3/1");

            // 1st round: efcdab
            // 2nd round: ebadcf
            // 3rd round: afedcb
            Assert::AreEqual("afedcb", test.GetFinalFormation().c_str());
        }

        // ---------------------------------------
        // SimplifyMoves
        // ---------------------------------------
        TEST_METHOD(December16b_SimplifyMoves_empty)
        {
            ProgramDancingMasterB test(6, 1);
            std::vector<std::string> commands = {};

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(true, moves.empty());

            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("abcdef", test.GetFinalFormation().c_str());
        }

        TEST_METHOD(December16b_SimplifyMoves_single)
        {
            ProgramDancingMasterB test(7, 1);
            std::vector<std::string> commands = {"x3/6"};

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(1, static_cast<int>(moves.size()));
            Assert::AreEqual("x3/6", moves[0]->GetCommand().c_str());

            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("abcgefd", test.GetFinalFormation().c_str());
        }

        /*
        executing the same partner move twice cancels each other out
        */
        TEST_METHOD(December16b_SimplifyMoves_cancelPartner)
        {
            ProgramDancingMasterB test(20, 1);
            std::vector<std::string> commands = { "pf/q", "s7", "pq/f" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(1, static_cast<int>(moves.size()));
            Assert::AreEqual("s7", moves[0]->GetCommand().c_str());

            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("nopqrstabcdefghijklm", test.GetFinalFormation().c_str());
        }

        /*
        executing the same exchange move twice without any other exchange move inbetween cancel each other out
        */
        TEST_METHOD(December16b_SimplifyMoves_cancelExchange)
        {
            ProgramDancingMasterB test(9, 1);
            std::vector<std::string> commands = { "x1/8", "x8/1" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(true, moves.empty());

            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("abcdefghi", test.GetFinalFormation().c_str());
        }

        /*
        different exchange moves should not be combined
        */
        TEST_METHOD(December16b_SimplifyMoves_severalExchanges)
        {
            ProgramDancingMasterB test(5, 5);
            std::vector<std::string> commands = { "x2/3", "x4/1" };
            // abcde -> abdce -> aedcb

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(2, static_cast<int>(moves.size()));

            // repeat 5 times -> keep swapping back and forth: abcde -> aedcb
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("aedcb", test.GetFinalFormation().c_str());
        }

        /*
        multiple spins without any exchange moves inbetween can be combined
        */
        TEST_METHOD(December16b_SimplifyMoves_spinCombination)
        {
            ProgramDancingMasterB test(10, 1);
            std::vector<std::string> commands = { "s3", "s4", "s1" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(1, static_cast<int>(moves.size()));
            Assert::AreEqual("s8", moves[0]->GetCommand().c_str());

            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("cdefghijab", test.GetFinalFormation().c_str());
        }

        /*
        a full spin rotation can be simplified or even removed entirely
        */
        TEST_METHOD(December16b_SimplifyMoves_spinRotation)
        {
            ProgramDancingMasterB test(7, 3);
            std::vector<std::string> commands = { "s2", "s3", "s5" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(1, static_cast<int>(moves.size()));
            Assert::AreEqual("s3", moves[0]->GetCommand().c_str());

            // repeat 3x: abcdefg -> efgabcd -> bcdefga -> fgabcde
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("fgabcde", test.GetFinalFormation().c_str());
        }

        /*
        - the two exchange commands cancel each other out when you take the spins into account
        - the spins can be combined into one
        */
        TEST_METHOD(December16b_SimplifyMoves_combination)
        {
            ProgramDancingMasterB test(8, 1);
            std::vector<std::string> commands = { "x1/5", "s3", "pg/e", "s3", "x3/7" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(2, static_cast<int>(moves.size()));

            // order shouldn't matter, so instead check whether the expected commands are included
            std::vector<std::string> simplifiedCommands;
            for (const auto& m : moves)
            {
                simplifiedCommands.push_back(m->GetCommand());
            }

            Assert::AreEqual(true, std::find(simplifiedCommands.begin(), simplifiedCommands.end(), "s6") != simplifiedCommands.end());
            Assert::AreEqual(true, std::find(simplifiedCommands.begin(), simplifiedCommands.end(), "pg/e") != simplifiedCommands.end());

            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("cdgfehab", test.GetFinalFormation().c_str());
        }

        /*
        cannot be simplified, repeat 3x
        */
        TEST_METHOD(December16b_SimplifyMoves_nonSimplified_repeated)
        {
            ProgramDancingMasterB test(5, 3);
            std::vector<std::string> commands = { "x1/4", "x2/4", "s2", "pc/b" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(4, static_cast<int>(moves.size()));

            // round 1: abcde -> aecdb -> aebdc -> dcaeb -> dbaec
            // round 2: dbaec -> dcaeb -> dcbea -> eadcb -> eadbc
            // round 3: eadbc -> ecdba -> ecabd -> bdeca -> cdeba
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("cdeba", test.GetFinalFormation().c_str());
        }

        /*
        exchanges have to be consecutive to be combined
        */
        TEST_METHOD(December16b_SimplifyMoves_multiExchange)
        {
            ProgramDancingMasterB test(5, 1);
            std::vector<std::string> commands = { "x1/4", "x2/4", "x4/1" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(3, static_cast<int>(moves.size()));

            // abcde -> aecdb -> aebdc -> acbde
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("acbde", test.GetFinalFormation().c_str());
        }

        /*
        as above, but repeated a few times
        */
        TEST_METHOD(December16b_SimplifyMoves_multiExchange_repeated)
        {
            ProgramDancingMasterB test(5, 5);
            std::vector<std::string> commands = { "x1/4", "x2/4", "x4/1" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(3, static_cast<int>(moves.size()));

            // repeat 5x
            // round 1: abcde -> aecdb -> aebdc -> acbde (repeat for rounds 3 and 5)
            // round 2: acbde -> aebdc -> aecdb -> abcde (repeat for round 4)
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("acbde", test.GetFinalFormation().c_str());
        }

        /*
        non-adjacent exchanges can cancel each other if the in-between move is not affected
        */
        TEST_METHOD(December16b_SimplifyMoves_exchangeSimplify)
        {
            ProgramDancingMasterB test(6, 1);
            std::vector<std::string> commands = { "x3/0", "x4/5", "x0/3" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(1, static_cast<int>(moves.size()));
            Assert::AreEqual("x4/5", moves[0]->GetCommand().c_str());

            // abcdef -> dbcaef -> dbcafe -> abcdfe
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("abcdfe", test.GetFinalFormation().c_str());
        }

        /*
        partner swaps also have to be consecutive to cancel each other
        */
        TEST_METHOD(December16b_SimplifyMoves_multiPartner)
        {
            ProgramDancingMasterB test(4, 1);
            std::vector<std::string> commands = { "pa/c", "pb/a", "pa/c" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(3, static_cast<int>(moves.size()));

            // abcd -> cbad -> cabd -> acbd
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("acbd", test.GetFinalFormation().c_str());
        }

        /*
        partner and exchange moves never cancel each other, even if they describe the same move
        (depends on the start formation)
        */
        TEST_METHOD(December16b_SimplifyMoves_partnerExchange)
        {
            ProgramDancingMasterB test(6, 1);
            std::vector<std::string> commands = { "pb/f", "x1/5" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(2, static_cast<int>(moves.size()));

            // abcdef -> afcdeb -> abcdef
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("abcdef", test.GetFinalFormation().c_str());
        }

        /*
        non-adjacent partner swaps can cancel each other if the in-between move is not affected
        */
        TEST_METHOD(December16b_SimplifyMoves_partnerSimplify)
        {
            ProgramDancingMasterB test(7, 1);
            std::vector<std::string> commands = { "pd/g", "pf/b", "pg/d" };

            std::vector<std::shared_ptr<DancingMove>> moves;
            Assert::AreEqual(true, test.CreateMoves(commands, moves));
            Assert::AreEqual(true, test.SimplifyMoves(moves));
            Assert::AreEqual(1, static_cast<int>(moves.size()));
            Assert::AreEqual("pf/b", moves[0]->GetCommand().c_str());

            // abcdefg -> abcgefd -> afcgebd -> afcdebg
            Assert::AreEqual(true, test.HandleDance(moves));
            Assert::AreEqual("afcdebg", test.GetFinalFormation().c_str());
        }
    };
}
