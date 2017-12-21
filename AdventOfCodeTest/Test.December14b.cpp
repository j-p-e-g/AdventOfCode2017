#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December14b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December14;

    TEST_CLASS(Test_December14b)
    {
    public:
        // ------------------------------
        // FindPointsInRegion
        // ------------------------------
        /*
        invalid point
        */
        TEST_METHOD(December14b_FindPointsInRegion_notInGrid)
        {
            DiskDefragmenterB test;
            test.ParseLine("flqrgnkx");
            std::vector<CodeUtils::Point> connected;
            Assert::AreEqual(false, test.FindPointsInRegion(CodeUtils::Point(129, 236), connected));
            Assert::AreEqual(true, connected.empty());
        }

        /*
        bit is false
        */
        TEST_METHOD(December14b_FindPointsInRegion_notARegion)
        {
            DiskDefragmenterB test;
            test.ParseLine("flqrgnkx");
            std::vector<CodeUtils::Point> connected;
            Assert::AreEqual(true, test.FindPointsInRegion(CodeUtils::Point(2, 3), connected));
            Assert::AreEqual(true, connected.empty());
        }

        /*
        In the example above, the following nine regions are visible, each marked with a distinct digit:

        11.2.3..-->
        .1.2.3.4
        ....5.6.
        7.8.55.9
        .88.5...
        88..5..8
        .8...8..
        88.8.88.-->
        |      |
        V      V

        Of particular interest is the region marked 8; while it does not appear contiguous in this small view, all of the squares marked 8 are connected when considering the whole 128x128 grid. 
        */
        TEST_METHOD(December14b_FindPointsInRegion_AoC_connected)
        {
            DiskDefragmenterB test;
            test.ParseLine("flqrgnkx");
            std::vector<CodeUtils::Point> connected;
            Assert::AreEqual(true, test.FindPointsInRegion(CodeUtils::Point(0,1), connected));
            // contains (0,0), (0,1) and (1,1)
            Assert::AreEqual(3, static_cast<int>(connected.size()));
            Assert::AreEqual(false, std::find(connected.begin(), connected.end(), CodeUtils::Point(0,0)) == connected.end());
            Assert::AreEqual(false, std::find(connected.begin(), connected.end(), CodeUtils::Point(0, 1)) == connected.end());
            Assert::AreEqual(false, std::find(connected.begin(), connected.end(), CodeUtils::Point(1, 1)) == connected.end());
        }

        TEST_METHOD(December14b_FindPointsInRegion_AoC_single)
        {
            DiskDefragmenterB test;
            test.ParseLine("flqrgnkx");
            std::vector<CodeUtils::Point> connected;
            Assert::AreEqual(true, test.FindPointsInRegion(CodeUtils::Point(2, 6), connected));
            Assert::AreEqual(1, static_cast<int>(connected.size()));
            Assert::AreEqual(true, CodeUtils::Point(2,6) == connected[0]);
        }

        /*
        In total, in this example, 1242 regions are present.
        */
        TEST_METHOD(December14b_GetNumRegions_AoC_test)
        {
            DiskDefragmenterB test;
            test.ParseLine("flqrgnkx");
            Assert::AreEqual(1242, test.GetNumRegions());
        }
    };
}
