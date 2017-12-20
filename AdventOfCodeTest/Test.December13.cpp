#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December13.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December13;

    TEST_CLASS(Test_December13)
    {
    public:
        // -----------------------------
        // Guard: GetIndexAtTime
        // -----------------------------
        /*
        guard without specified range
        */
        TEST_METHOD(December13_Guard_zeroRange)
        {
            Guard test(0, 0);
            Assert::AreEqual(false, test.IsValid());
            Assert::AreEqual(-1, test.GetIndexAtTime(0));
        }

        /*
        guard with invalid range
        */
        TEST_METHOD(December13_Guard_negativeRange)
        {
            Guard test(-2, -1);
            Assert::AreEqual(false, test.IsValid());
            Assert::AreEqual(-1, test.GetIndexAtTime(0));
        }

        /*
        guard with starting index out of bounds
        */
        TEST_METHOD(December13_Guard_negativeIndex)
        {
            Guard test(2, -1);
            Assert::AreEqual(false, test.IsValid());
            Assert::AreEqual(-1, test.GetIndexAtTime(0));
        }

        /*
        guard with starting index out of bounds
        */
        TEST_METHOD(December13_Guard_invalidStartingIndex)
        {
            Guard test(5, 5);
            Assert::AreEqual(false, test.IsValid());
            Assert::AreEqual(-1, test.GetIndexAtTime(0));
        }

        /*
        guard with valid range and index
        */
        TEST_METHOD(December13_Guard_valid)
        {
            Guard test(3, 2);
            Assert::AreEqual(true, test.IsValid());
            Assert::AreEqual(2, test.GetIndexAtTime(0));
        }

        /*
        GetIndexAtTime
        */
        TEST_METHOD(December13_Guard_GetIndexAtTime_negativeTime)
        {
            Guard test(2, 0, DIR_Up);
            Assert::AreEqual(-1, test.GetIndexAtTime(-2));
        }

        TEST_METHOD(December13_Guard_GetIndexAtTime_Up)
        {
            Guard test(5, 1, DIR_Up);
            Assert::AreEqual(4, test.GetIndexAtTime(3));
        }

        TEST_METHOD(December13_Guard_GetIndexAtTime_Down)
        {
            Guard test(4, 2, DIR_Down);
            Assert::AreEqual(0, test.GetIndexAtTime(2));
        }

        TEST_METHOD(December13_Guard_GetIndexAtTime_Up_switchDir)
        {
            Guard test(3, 2, DIR_Up);
            Assert::AreEqual(1, test.GetIndexAtTime(1));
        }

        TEST_METHOD(December13_Guard_GetIndexAtTime_Down_switchDir)
        {
            Guard test(7, 3, DIR_Down);
            Assert::AreEqual(2, test.GetIndexAtTime(5));
        }

        // -----------------------------
        // Firewall: ParseLine
        // -----------------------------
        /*
        empty line
        */
        TEST_METHOD(December13_ParseLine_empty)
        {
            Firewall firewall;
            Assert::AreEqual(false, firewall.ParseLine(""));
        }

        /*
        missing colon
        */
        TEST_METHOD(December13_ParseLine_noColon)
        {
            Firewall firewall;
            Assert::AreEqual(false, firewall.ParseLine("17 53"));
        }

        /*
        missing index
        */
        TEST_METHOD(December13_ParseLine_missingIndex)
        {
            Firewall firewall;
            Assert::AreEqual(false, firewall.ParseLine(": 2"));
        }

        /*
        missing index
        */
        TEST_METHOD(December13_ParseLine_missingRange)
        {
            Firewall firewall;
            Assert::AreEqual(false, firewall.ParseLine("33 :"));
        }

        /*
        negative index
        */
        TEST_METHOD(December13_ParseLine_negativeIndex)
        {
            Firewall firewall;
            Assert::AreEqual(false, firewall.ParseLine("-3:7"));
        }

        /*
        negative range
        */
        TEST_METHOD(December13_ParseLine_negativeRange)
        {
            Firewall firewall;
            Assert::AreEqual(false, firewall.ParseLine("18 : -92"));
        }

        /*
        unexpected extra numbers
        */
        TEST_METHOD(December13_ParseLine_extraNumbers)
        {
            Firewall firewall;
            Assert::AreEqual(false, firewall.ParseLine("97 : 2 : 31"));
        }

        /*
        valid format
        */
        TEST_METHOD(December13_ParseLine_valid)
        {
            Firewall firewall;
            Assert::AreEqual(true, firewall.ParseLine("8:21"));
        }

        /*
        valid format containing lots of spaces
        */
        TEST_METHOD(December13_ParseLine_validWithSpaces)
        {
            Firewall firewall;
            Assert::AreEqual(true, firewall.ParseLine(" 95 : 250 "));
        }

        // -----------------------------
        // Firewall: GetIntruderCaughtLocations
        // -----------------------------
        /*
        no guards -> nobody gets caught
        */
        TEST_METHOD(December13_GetIntruderCaughtLocations_noGuards)
        {
            Firewall firewall;

            std::vector<int> caughtLocations;
            firewall.GetIntruderCaughtLocations(0, caughtLocations);

            Assert::AreEqual(true, caughtLocations.empty());
        }

        /*
        1 guard, get caught
        */
        TEST_METHOD(December13_GetIntruderCaughtLocations_simple_caught)
        {
            Firewall firewall;

            std::vector<int> caughtLocations;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 1, DIR_Down));
            firewall.GetIntruderCaughtLocations(1, caughtLocations);

            // caught at location 0
            Assert::AreEqual(1, (int)caughtLocations.size());
            Assert::AreEqual(false, std::find(caughtLocations.begin(), caughtLocations.end(), 0) == caughtLocations.end());
        }

        /*
        1 guard, don't get caught
        */
        TEST_METHOD(December13_GetIntruderCaughtLocations_simple_notCaught)
        {
            Firewall firewall;

            std::vector<int> caughtLocations;
            firewall.AddGuard(0, std::make_shared<Guard>(5, 1, DIR_Up));
            firewall.GetIntruderCaughtLocations(6, caughtLocations);

            Assert::AreEqual(true, caughtLocations.empty());
        }

        /*
        1 guard at a later location, get caught
        */
        TEST_METHOD(December13_GetIntruderCaughtLocations_later_caught)
        {
            Firewall firewall;

            std::vector<int> caughtLocations;
            firewall.AddGuard(3, std::make_shared<Guard>(4, 2, DIR_Up));
            firewall.GetIntruderCaughtLocations(1, caughtLocations);

            // caught at location 3
            Assert::AreEqual(1, (int)caughtLocations.size());
            Assert::AreEqual(false, std::find(caughtLocations.begin(), caughtLocations.end(), 3) == caughtLocations.end());
        }

        /*
        1 guard at later location, don't get caught
        */
        TEST_METHOD(December13_GetIntruderCaughtLocations_later_notCaught)
        {
            Firewall firewall;

            std::vector<int> caughtLocations;
            firewall.AddGuard(8, std::make_shared<Guard>(2, 0, DIR_Down));
            firewall.GetIntruderCaughtLocations(3, caughtLocations);

            Assert::AreEqual(true, caughtLocations.empty());
        }

        /*
        several guards, get caught by some of them
        */
        TEST_METHOD(December13_GetIntruderCaughtLocations_multipleGuards)
        {
            Firewall firewall;

            std::vector<int> caughtLocations;
            firewall.AddGuard(0, std::make_shared<Guard>(2, 1, DIR_Down));
            firewall.AddGuard(2, std::make_shared<Guard>(3, 0, DIR_Up));
            firewall.AddGuard(3, std::make_shared<Guard>(5, 4, DIR_Down));
            firewall.GetIntruderCaughtLocations(1, caughtLocations);

            // caught at locations 0 and 3
            Assert::AreEqual(2, (int)caughtLocations.size());
            Assert::AreEqual(false, std::find(caughtLocations.begin(), caughtLocations.end(), 0) == caughtLocations.end());
            Assert::AreEqual(false, std::find(caughtLocations.begin(), caughtLocations.end(), 3) == caughtLocations.end());
        }

        /*
        0: 3
        1: 2
        4: 4
        6: 4

        In this situation, you are caught in layers 0 and 6, because your packet entered the layer when its scanner was at the top when you entered it.
        */
        TEST_METHOD(December13_GetIntruderCaughtLocations_AoC)
        {
            Firewall firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 0));
            firewall.AddGuard(1, std::make_shared<Guard>(2, 0));
            firewall.AddGuard(4, std::make_shared<Guard>(4, 0));
            firewall.AddGuard(6, std::make_shared<Guard>(4, 0));

            std::vector<int> caughtLocations;
            firewall.GetIntruderCaughtLocations(0, caughtLocations);

            // contains 0 and 6
            Assert::AreEqual(2, (int)caughtLocations.size());
            Assert::AreEqual(false, std::find(caughtLocations.begin(), caughtLocations.end(), 0) == caughtLocations.end());
            Assert::AreEqual(false, std::find(caughtLocations.begin(), caughtLocations.end(), 6) == caughtLocations.end());
        }

        TEST_METHOD(December13_GetSecurityScore_notCaught)
        {
            Firewall firewall;
            firewall.AddGuard(1, std::make_shared<Guard>(2, 0));

            Assert::AreEqual(0, firewall.GetSecurityScore(2, 3));
        }

        TEST_METHOD(December13_GetSecurityScore_caughtWithZeroScore)
        {
            Firewall firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 2, DIR_Down));

            // startingPenalty is zero, so being caught at index 0 is not penalized at all
            Assert::AreEqual(0, firewall.GetSecurityScore(2, 0));
        }

        TEST_METHOD(December13_GetSecurityScore_caughtWithHighScore)
        {
            Firewall firewall;
            firewall.AddGuard(3, std::make_shared<Guard>(8, 3, DIR_Up));
            firewall.AddGuard(5, std::make_shared<Guard>(4, 1, DIR_Up));

            // depth * range
            Assert::AreEqual(20, firewall.GetSecurityScore(0, 0));
        }

        /*
        0: 3
        1: 2
        4: 4
        6: 4

        In this situation, you are caught in layers 0 and 6, because your packet entered the layer when its scanner was at the top when you entered it. 

        The severity of getting caught on a layer is equal to its depth multiplied by its range. (Ignore layers in which you do not get caught.) The severity of the whole trip is the sum of these values. In the example above, the trip severity is 0*3 + 6*4 = 24.
        */
        TEST_METHOD(December13_AoC_test)
        {
            Firewall firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 0));
            firewall.AddGuard(1, std::make_shared<Guard>(2, 0));
            firewall.AddGuard(4, std::make_shared<Guard>(4, 0));
            firewall.AddGuard(6, std::make_shared<Guard>(4, 0));

            // being caught at index 0 is not penalized
            Assert::AreEqual(24, firewall.GetSecurityScore(0, 0));
            // if penalizing already at index 0
            Assert::AreEqual(31, firewall.GetSecurityScore(0, 1));
        }
    };
}
