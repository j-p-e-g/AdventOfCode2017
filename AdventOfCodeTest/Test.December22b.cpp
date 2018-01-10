#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December22b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December22;

    TEST_CLASS(Test_December22b)
    {
    public:
        TEST_METHOD(December22b_ReverseDirection)
        {
            InfectedGridB test;

            test.ReverseDirection();
            Assert::AreEqual(true, Coord::Down == test.GetDirection());

            test.ReverseDirection();
            Assert::AreEqual(true, Coord::Up == test.GetDirection());
        }

        /*
        The virus starts at a clean cell.

        Clean nodes become weakened.
        If it is clean, it turns left.
        */
        TEST_METHOD(December22b_HandleBurst_cleanCell)
        {
            InfectedGridB test;
            test.ParseLine(".");
            test.HandleSingleBurst();

            Assert::AreEqual(true, Coord::Left == test.GetDirection());
            Assert::AreEqual(true, Coord::Point(-1, 0) == test.GetVirusPosition());
            Assert::AreEqual('W', test.GetMatrix().Get(0, 0));
            Assert::AreEqual(0, test.GetNumInfectiousBursts());
        }

        /*
        The virus starts at a weakened cell.

        Weakened nodes become infected.
        If it is weakened, it does not turn, and will continue moving in the same direction.
        */
        TEST_METHOD(December22b_HandleBurst_weakenedCell)
        {
            InfectedGridB test;
            test.ParseLine("W");
            test.HandleSingleBurst();

            Assert::AreEqual(true, Coord::Up == test.GetDirection());
            Assert::AreEqual(true, Coord::Point(0, -1) == test.GetVirusPosition());
            Assert::AreEqual('#', test.GetMatrix().Get(0, 0));
            Assert::AreEqual(1, test.GetNumInfectiousBursts());
        }

        /*
        The virus starts at an infected cell.

        Infected nodes become flagged.
        If it is infected, it turns right.
        */
        TEST_METHOD(December22b_HandleBurst_infectedCell)
        {
            InfectedGridB test;
            test.ParseLine("#");
            test.HandleSingleBurst();

            Assert::AreEqual(true, Coord::Right == test.GetDirection());
            Assert::AreEqual(true, Coord::Point(1, 0) == test.GetVirusPosition());
            Assert::AreEqual('F', test.GetMatrix().Get(0, 0));
            Assert::AreEqual(0, test.GetNumInfectiousBursts());
        }

        /*
        The virus starts at a flagged cell.

        Flagged nodes become clean.
        If it is flagged, it reverses direction, and will go back the way it came.
        */
        TEST_METHOD(December22b_HandleBurst_flaggedCell)
        {
            InfectedGridB test;
            test.ParseLine("F");
            test.HandleSingleBurst();

            Assert::AreEqual(true, Coord::Down == test.GetDirection());
            Assert::AreEqual(true, Coord::Point(0, 1) == test.GetVirusPosition());
            Assert::AreEqual('.', test.GetMatrix().Get(0, 0));
            Assert::AreEqual(0, test.GetNumInfectiousBursts());
        }

        /*
        after 7 bursts, the map looks like this:

        . . . . . . . . .
        . . . . . . . . .
        . . . . . . . . .
        . . W W . # . . .
        .[.]# . W . . . .
        . . . . . . . . .
        . . . . . . . . .
        . . . . . . . . .
        */
        TEST_METHOD(December22b_GetNumInfectiousBursts_AoC_test_7)
        {
            InfectedGridB test;
            test.ParseLine("..#");
            test.ParseLine("#..");
            test.ParseLine("...");
            test.HandleBursts(7);

            Assert::AreEqual(1, test.GetNumInfectiousBursts());
            // already infected before
            Assert::AreEqual('#', test.GetMatrix().Get(2, 0));
            // newly infected
            Assert::AreEqual('#', test.GetMatrix().Get(-1, 1));

            const Coord::Point pos = test.GetVirusPosition();
            Assert::AreEqual(-2, pos.x);
            Assert::AreEqual(1, pos.y);
        }

        /*
        Of the first 100 bursts, 26 will result in infection.
        */
        TEST_METHOD(December22b_GetNumInfectiousBursts_AoC_test_100)
        {
            InfectedGridB test;
            test.ParseLine("..#");
            test.ParseLine("#..");
            test.ParseLine("...");
            test.HandleBursts(100);

            Assert::AreEqual(26, test.GetNumInfectiousBursts());
        }

        /*
        [...] of the first 10000000 bursts, 2511944 will result in infection.
        Takes a few seconds.
        */
        //TEST_METHOD(December22b_GetNumInfectiousBursts_AoC_test_10000000)
        //{
        //    InfectedGridB test;
        //    test.ParseLine("..#");
        //    test.ParseLine("#..");
        //    test.ParseLine("...");
        //    test.HandleBursts(10000000);

        //    Assert::AreEqual(2511944, test.GetNumInfectiousBursts());
        //}
    };
}
