#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December19b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December19;

    TEST_CLASS(Test_December19b)
    {
    public:
        TEST_METHOD(December19b_GetPathLength_empty)
        {
            NetworkDiagramB test;
            Assert::AreEqual(0, test.GetPathLength());
        }

        /*
            |
        */
        TEST_METHOD(December19b_GetPathLength_single)
        {
            NetworkDiagramB test;
            test.ParseLine("  |  ");

            Assert::AreEqual(true, test.ProcessDiagram());
            Assert::AreEqual(1, test.GetPathLength());
        }

        /*
                 |
            +-A--+
            B
        */
        TEST_METHOD(December19b_GetPathLength_simple)
        {
            NetworkDiagramB test;
            test.ParseLine("     |");
            test.ParseLine("+-A--+");
            test.ParseLine("B");

            Assert::AreEqual(true, test.ProcessDiagram());
            Assert::AreEqual(8, test.GetPathLength());
        }

        /*
                |
                |  +--+
                A  |  C
            F---|----E|--+
                |  |  |  D
                +B-+  +--+

        This would result in a total of 38 steps.
        */
        TEST_METHOD(December19b_GetPathLength_AoC_test)
        {
            NetworkDiagramB test;
            test.ParseLine("    |         ");
            test.ParseLine("    |  +--+   ");
            test.ParseLine("    A  |  C   ");
            test.ParseLine("F---|----E|--+");
            test.ParseLine("    |  |  |  D");
            test.ParseLine("    +B-+  +--+");

            Assert::AreEqual(true, test.ProcessDiagram());
            Assert::AreEqual(38, test.GetPathLength());
        }
    };
}
