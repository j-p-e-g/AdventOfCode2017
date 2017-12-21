#include "stdafx.h"

#include <set>

#include "CppUnitTest.h"
#include "../AdventOfCode/December13b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December13;

    TEST_CLASS(Test_December13b)
    {
    public:
        // ------------------------------------
        // GetMaxNumberOfGuardCombinations
        // ------------------------------------
        /*
        no guards -> only one setup possible
        */
        TEST_METHOD(December13b_GetMaxNumberOfGuardCombinations_noGuards)
        {
            FirewallB firewall;
            Assert::AreEqual(1, firewall.GetMaxNumberOfGuardCombinations());
        }

        /*
        1 guard, range 3 -> 3 combinations
        */
        TEST_METHOD(December13b_GetMaxNumberOfGuardCombinations_singleGuard)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 0, DIR_Down));
            Assert::AreEqual(3, firewall.GetMaxNumberOfGuardCombinations());
        }

        /*
        multiple guards, range 1 -> 1 combination
        */
        TEST_METHOD(December13b_GetMaxNumberOfGuardCombinations_allRangeOne)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(1, 0, DIR_Down));
            firewall.AddGuard(2, std::make_shared<Guard>(1, 0, DIR_Up));
            firewall.AddGuard(3, std::make_shared<Guard>(1, 0, DIR_Down));
            Assert::AreEqual(1, firewall.GetMaxNumberOfGuardCombinations());
        }

        /*
        multiple guards, different ranges
        */
        TEST_METHOD(December13b_GetMaxNumberOfGuardCombinations_different)
        {
            FirewallB firewall;
            firewall.AddGuard(3, std::make_shared<Guard>(2, 0, DIR_Down));
            firewall.AddGuard(5, std::make_shared<Guard>(3, 1, DIR_Up));
            Assert::AreEqual(6, firewall.GetMaxNumberOfGuardCombinations());
        }

        /*
        multiple guards, different ranges
        */
        TEST_METHOD(December13b_GetMaxNumberOfGuardCombinations_highRanges)
        {
            FirewallB firewall;
            firewall.AddGuard(1, std::make_shared<Guard>(14, 0, DIR_Down));
            firewall.AddGuard(2, std::make_shared<Guard>(7, 0, DIR_Down));
            firewall.AddGuard(3, std::make_shared<Guard>(28, 0, DIR_Down));
            firewall.AddGuard(4, std::make_shared<Guard>(2, 0, DIR_Down));
            firewall.AddGuard(5, std::make_shared<Guard>(10, 0, DIR_Down));
            Assert::AreEqual(280, firewall.GetMaxNumberOfGuardCombinations());
        }

        // ------------------------------------
        // AddTimesBlockedByGuards
        // ------------------------------------
        /*
        no guards -> never blocked
        */
        TEST_METHOD(December13b_AddTimesBlockedByGuards_noGuards)
        {
            FirewallB firewall;
            std::vector<TimeBlock> blockedTimes;
            firewall.AddTimesBlockedByGuards(blockedTimes, 7);
            Assert::AreEqual(true, blockedTimes.empty());
        }

        /*
        single guard at location 0 and starting at slot 0
        */
        TEST_METHOD(December13b_AddTimesBlockedByGuards_simple)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 0, DIR_Down));

            std::vector<TimeBlock> blockedTimes;
            firewall.AddTimesBlockedByGuards(blockedTimes, 8);

            // contains (0, 4)
            Assert::AreEqual(1, static_cast<int>(blockedTimes.size()));
            Assert::AreEqual(0, blockedTimes[0].start);
            Assert::AreEqual(4, blockedTimes[0].offset);
        }

        /*
        single guard at location 0 but starting at a different slot
        */
        TEST_METHOD(December13b_AddTimesBlockedByGuards_differentSlot)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(4, 2, DIR_Down));

            std::vector<TimeBlock> blockedTimes;
            firewall.AddTimesBlockedByGuards(blockedTimes, 10);

            // contains (2, 6)
            Assert::AreEqual(1, static_cast<int>(blockedTimes.size()));
            Assert::AreEqual(2, blockedTimes[0].start);
            Assert::AreEqual(6, blockedTimes[0].offset);
        }

        /*
        single guard starting at slot 0 but at a different location
        */
        TEST_METHOD(December13b_AddTimesBlockedByGuards_differentLocation)
        {
            FirewallB firewall;
            // is zero at times 0, 8, 16, ... 
            // but the invader can only reach it at the earliest by time 15
            // so if I start out at time 0, when I reach this guard it will be in slot 1 (16-15), meaning the guard instead blocks times 1, 9, 17, ...
            firewall.AddGuard(15, std::make_shared<Guard>(5, 0, DIR_Up));

            std::vector<TimeBlock> blockedTimes;
            firewall.AddTimesBlockedByGuards(blockedTimes, 50);

            // contains (1, 8)
            Assert::AreEqual(1, static_cast<int>(blockedTimes.size()));
            Assert::AreEqual(1, blockedTimes[0].start);
            Assert::AreEqual(8, blockedTimes[0].offset);
        }

        /*
        single guard starting at a different location and a different slot
        */
        TEST_METHOD(December13b_AddTimesBlockedByGuards_differentLocationAndSlot)
        {
            FirewallB firewall;
            // is zero at times 9, 23, 37, ...
            // but the slot means it actually blocks 2 turns earlier than that
            firewall.AddGuard(2, std::make_shared<Guard>(8, 5, DIR_Up));

            std::vector<TimeBlock> blockedTimes;
            firewall.AddTimesBlockedByGuards(blockedTimes, 25);

            // contains (7, 14)
            Assert::AreEqual(1, static_cast<int>(blockedTimes.size()));
            Assert::AreEqual(7, blockedTimes[0].start);
            Assert::AreEqual(14, blockedTimes[0].offset);
        }

        /*
        by the time slot zero is first blocked, the max time is already over
        */
        TEST_METHOD(December13b_AddTimesBlockedByGuards_firstBlockedAfterMaxTime)
        {
            FirewallB firewall;
            // is zero at times 7, 29 but first reachable at 8 and capped at 25
            firewall.AddGuard(8, std::make_shared<Guard>(12, 7, DIR_Down));

            std::vector<TimeBlock> blockedTimes;
            firewall.AddTimesBlockedByGuards(blockedTimes, 25);
            Assert::AreEqual(true, blockedTimes.empty());
        }

        // ------------------------------------
        // GetMinDelayNeededToAvoidDetection
        // ------------------------------------
        /*
        no guards -> nobody gets caught
        */
        TEST_METHOD(December13b_GetMinDelayNeededToAvoidDetection_noGuards)
        {
            FirewallB firewall;
            Assert::AreEqual(0, firewall.GetMinDelayNeededToAvoidDetection());
        }

        /*
        1 guard, needs delay
        */
        TEST_METHOD(December13b_GetMinDelayNeededToAvoidDetection_simpleDelay)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 0, DIR_Down));
            Assert::AreEqual(1, firewall.GetMinDelayNeededToAvoidDetection());
        }

        /*
        1 guard, doesn't need delay
        */
        TEST_METHOD(December13b_GetMinDelayNeededToAvoidDetection_simpleNoDelay)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(2, 1, DIR_Up));
            Assert::AreEqual(0, firewall.GetMinDelayNeededToAvoidDetection());
        }

        /*
        3 guards: earliest start is 4

        0: [G] [G]     [ ]
           [ ] [ ]     [G]
           [ ]         [ ]
           [ ]        

        1: [ ] [ ]     [G]
           [G] [G]     [ ]
           [ ]         [ ]
           [ ]        

        2: [ ] [G]     [ ]
           [ ] [ ]     [G]
           [G]         [ ]
           [ ]        

        3: [ ] [ ]     [ ]
           [ ] [G]     [ ]
           [ ]         [G]
           [G]        

        4: [ ] [G]     [ ]
           [ ] [ ]     [G]
           [G]         [ ]
           [ ]        

        5: [ ] [ ]     [G]
           [G] [G]     [ ]
           [ ]         [ ]
           [ ]        

        6: [G] [G]     [ ]
           [ ] [ ]     [G]
           [ ]         [ ]
           [ ]        

        7: [ ] [ ]     [ ]
           [G] [G]     [ ]
           [ ]         [G]
           [ ]        
           */
        TEST_METHOD(December13b_GetMinDelayNeededToAvoidDetection_multipleGuards)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(4, 0, DIR_Up));
            firewall.AddGuard(1, std::make_shared<Guard>(2, 0, DIR_Up));
            firewall.AddGuard(3, std::make_shared<Guard>(3, 1, DIR_Down));
            Assert::AreEqual(4, firewall.GetMinDelayNeededToAvoidDetection());
        }

        /*
        2 guards, impossible to avoid detection
        */
        TEST_METHOD(December13b_GetMinDelayNeededToAvoidDetection_impossible)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(2, 0, DIR_Down));
            firewall.AddGuard(1, std::make_shared<Guard>(2, 0, DIR_Down));
            Assert::AreEqual(-1, firewall.GetMinDelayNeededToAvoidDetection());
        }

        /*
        0: 3
        1: 2
        4: 4
        6: 4

        Because all smaller delays would get you caught, the fewest number of picoseconds you would need to delay to get through safely is 10.
        */
        TEST_METHOD(December13b_AoC_test)
        {
            FirewallB firewall;
            firewall.AddGuard(0, std::make_shared<Guard>(3, 0));
            firewall.AddGuard(1, std::make_shared<Guard>(2, 0));
            firewall.AddGuard(4, std::make_shared<Guard>(4, 0));
            firewall.AddGuard(6, std::make_shared<Guard>(4, 0));

            Assert::AreEqual(10, firewall.GetMinDelayNeededToAvoidDetection());
        }
    };
}
