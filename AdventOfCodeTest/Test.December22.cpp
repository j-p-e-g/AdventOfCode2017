#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December22.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December22;

    TEST_CLASS(Test_December22)
    {
    public:
        TEST_METHOD(December22_TurnLeft)
        {
            InfectedGrid test;

            test.TurnLeft();
            Assert::AreEqual(true, Coord::Left == test.GetDirection());

            test.TurnLeft();
            Assert::AreEqual(true, Coord::Down == test.GetDirection());

            test.TurnLeft();
            Assert::AreEqual(true, Coord::Right == test.GetDirection());

            test.TurnLeft();
            Assert::AreEqual(true, Coord::Up == test.GetDirection());
        }

        TEST_METHOD(December22_TurnRight)
        {
            InfectedGrid test;

            test.TurnRight();
            Assert::AreEqual(true, Coord::Right == test.GetDirection());

            test.TurnRight();
            Assert::AreEqual(true, Coord::Down == test.GetDirection());

            test.TurnRight();
            Assert::AreEqual(true, Coord::Left == test.GetDirection());

            test.TurnRight();
            Assert::AreEqual(true, Coord::Up == test.GetDirection());
        }

        /*
        A matrix consisting of a single infected cell

             #
        */
        TEST_METHOD(December22_ParseLine_tiny)
        {
            InfectedGrid test;
            test.ParseLine("#");

            const Coord::Point startPoint = test.GetVirusPosition();
            Assert::AreEqual(0, startPoint.x);
            Assert::AreEqual(0, startPoint.y);
            Assert::AreEqual('#', test.GetMatrix().Get(0, 0));
        }

        /*
        For example, suppose you are given a map like this:

        ..#
        #..
        ...
        */
        TEST_METHOD(December22_ParseLine_AoC_test)
        {
            InfectedGrid test;
            test.ParseLine("..#");
            test.ParseLine("#..");
            test.ParseLine("...");

            const Coord::Point startPoint = test.GetVirusPosition();
            Assert::AreEqual(1, startPoint.x);
            Assert::AreEqual(1, startPoint.y);

            Assert::AreEqual('.', test.GetMatrix().Get(startPoint));
            Assert::AreEqual('#', test.GetMatrix().Get(startPoint + Coord::Point(-1, 0)));
            Assert::AreEqual('#', test.GetMatrix().Get(startPoint + Coord::Point(1, -1)));
        }

        /*
        The virus starts at a non-infected cell.

        The virus carrier is on a clean node, so it turns left, infects the node, and moves left.
        */
        TEST_METHOD(December22_HandleBurst_cleanCell)
        {
            InfectedGrid test;
            test.ParseLine(".");
            test.HandleSingleBurst();

            Assert::AreEqual(true, Coord::Left == test.GetDirection());
            Assert::AreEqual(true, Coord::Point(-1, 0) == test.GetVirusPosition());
            Assert::AreEqual('#', test.GetMatrix().Get(0, 0));
            Assert::AreEqual(1, test.GetNumInfectiousBursts());
        }

        /*
        The virus starts at an infected cell.

        The virus carrier is on an infected node, so it turns right, cleans the node, and moves right.
        */
        TEST_METHOD(December22_HandleBurst_infectedCell)
        {
            InfectedGrid test;
            test.ParseLine("#");
            test.HandleSingleBurst();

            Assert::AreEqual(true, Coord::Right == test.GetDirection());
            Assert::AreEqual(true, Coord::Point(1, 0) == test.GetVirusPosition());
            Assert::AreEqual('.', test.GetMatrix().Get(0, 0));
            Assert::AreEqual(0, test.GetNumInfectiousBursts());
        }

        TEST_METHOD(December22_GetNumInfectiousBursts_noBursts)
        {
            InfectedGrid test;
            Assert::AreEqual(0, test.GetNumInfectiousBursts());
        }

        /*
        . . . . . . . . .
        . . . . . . . . .
        . . . . . . . . .
        . . # .[.]# . . .
        . . # # # . . . .
        . . . . . . . . .
        . . . . . . . . .
        . . . . . . . . .

        After the [...] actions, a total of 7 bursts of activity had taken place. Of them, 5 bursts of activity caused an infection.
        */
        TEST_METHOD(December22_GetNumInfectiousBursts_AoC_test_7)
        {
            InfectedGrid test;
            test.ParseLine("..#");
            test.ParseLine("#..");
            test.ParseLine("...");
            test.HandleBursts(7);

            Assert::AreEqual(5, test.GetNumInfectiousBursts());
            
            const Coord::Point pos = test.GetVirusPosition();
            Assert::AreEqual(1, pos.x);
            Assert::AreEqual(0, pos.y);
        }

        /*
        After a total of 70, the grid looks like this, with the virus carrier facing up:

        . . . . . # # . .
        . . . . # . . # .
        . . . # . . . . #
        . . # . #[.]. . #
        . . # . # . . # .
        . . . . . # # . .
        . . . . . . . . .
        . . . . . . . . .

        By this time, 41 bursts of activity caused an infection (though most of those nodes have since been cleaned).
        */
        TEST_METHOD(December22_GetNumInfectiousBursts_AoC_test_70)
        {
            InfectedGrid test;
            test.ParseLine("..#");
            test.ParseLine("#..");
            test.ParseLine("...");
            test.HandleBursts(70);

            Assert::AreEqual(41, test.GetNumInfectiousBursts());
        }

        /*
        After a total of 10000 bursts of activity, 5587 bursts will have caused an infection.
        */
        TEST_METHOD(December22_GetNumInfectiousBursts_AoC_test_10000)
        {
            InfectedGrid test;
            test.ParseLine("..#");
            test.ParseLine("#..");
            test.ParseLine("...");
            test.HandleBursts(10000);

            Assert::AreEqual(5587, test.GetNumInfectiousBursts());
        }
    };
}
