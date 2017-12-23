#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December15b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December15;

    TEST_CLASS(Test_December15b)
    {
    public:
        // ----------------------------------------
        // Generator: CalculateNextNumber
        // ----------------------------------------
        /*
        Using the example starting values given above, the generators now produce the following first five values each:

        --Gen. A--  --Gen. B--
        1352636452  1233683848
        1992081072   862516352
        530830436  1159784568
        1980017072  1616057672
        740335192   412269392
        */
        TEST_METHOD(December15b_CalculateNextNumber_genA)
        {
            std::shared_ptr<GeneratorB> genA = std::make_shared<GeneratorB>(65, 16807, 2147483647, 4);

            Assert::AreEqual(1352636452, genA->CalculateNextNumber());
            Assert::AreEqual(1992081072, genA->CalculateNextNumber());
            Assert::AreEqual(530830436, genA->CalculateNextNumber());
            Assert::AreEqual(1980017072, genA->CalculateNextNumber());
            Assert::AreEqual(740335192, genA->CalculateNextNumber());
        }

        TEST_METHOD(December15b_CalculateNextNumber_genB)
        {
            std::shared_ptr<GeneratorB> genB = std::make_shared<GeneratorB>(8921, 48271, 2147483647, 8);
            Assert::AreEqual(1233683848, genB->CalculateNextNumber());
            Assert::AreEqual(862516352, genB->CalculateNextNumber());
            Assert::AreEqual(1159784568, genB->CalculateNextNumber());
            Assert::AreEqual(1616057672, genB->CalculateNextNumber());
            Assert::AreEqual(412269392, genB->CalculateNextNumber());
        }

        /*
        Now, it's not until the 1056th pair that the judge finds the first match:

        --Gen. A--  --Gen. B--
        1023762912   896885216
        */
        TEST_METHOD(December15b_CountMatchingResults_AoC_test)
        {
            DuelingGeneratorJudgeB test;
            test.AddGenerator(std::shared_ptr<Generator>(new GeneratorB(65, 16807, 2147483647, 4)));
            test.AddGenerator(std::shared_ptr<Generator>(new GeneratorB(8921, 48271, 2147483647, 8)));
            // no matches found in the first 5 runs
            Assert::AreEqual(0, test.CountMatchingResults(5));
            // 1 match found within the _next_ 1051 runs (1056-5)
            Assert::AreEqual(1, test.CountMatchingResults(1051));
        }
    };
}
