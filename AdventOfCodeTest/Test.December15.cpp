#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December15.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December15;

    TEST_CLASS(Test_December15)
    {
    public:
        // ----------------------------------------
        // Generator: CalculateNextNumber
        // ----------------------------------------
        /*
        For example, suppose that for starting values, generator A uses 65, while generator B uses 8921. Then, the first five pairs of generated values are:

        --Gen. A--  --Gen. B--
        1092455   430625591
        1181022009  1233683848
        245556042  1431495498
        1744312007   137874439
        1352636452   285222916
        */
        TEST_METHOD(December15_CalculateNextNumber_genA)
        {
            std::shared_ptr<Generator> genA = std::make_shared<Generator>(65, 16807, 2147483647);

            Assert::AreEqual(1092455, genA->CalculateNextNumber());
            Assert::AreEqual(1181022009, genA->CalculateNextNumber());
            Assert::AreEqual(245556042, genA->CalculateNextNumber());
            Assert::AreEqual(1744312007, genA->CalculateNextNumber());
            Assert::AreEqual(1352636452, genA->CalculateNextNumber());
        }

        TEST_METHOD(December15_CalculateNextNumber_genB)
        {
            std::shared_ptr<Generator> genB = std::make_shared<Generator>(8921, 48271, 2147483647);
            Assert::AreEqual(430625591, genB->CalculateNextNumber());
            Assert::AreEqual(1233683848, genB->CalculateNextNumber());
            Assert::AreEqual(1431495498, genB->CalculateNextNumber());
            Assert::AreEqual(137874439, genB->CalculateNextNumber());
            Assert::AreEqual(285222916, genB->CalculateNextNumber());
        }

        // ----------------------------------------
        // DuelingGeneratorJudge
        // ----------------------------------------
        /*
        */
        TEST_METHOD(December15_CompareGeneratorOutcomes_different)
        {
            std::shared_ptr<Generator> genA = std::make_shared<Generator>(65, 16807, 2147483647);
            std::shared_ptr<Generator> genB = std::make_shared<Generator>(8921, 48271, 2147483647);

            DuelingGeneratorJudge test;
            test.AddGenerator(genA);
            test.AddGenerator(genB);
            // run one round and compare the results
            Assert::AreEqual(false, test.CompareGeneratorOutcomes());
        }

        TEST_METHOD(December15_CompareGeneratorOutcomes_same)
        {
            std::shared_ptr<Generator> genA = std::make_shared<Generator>(1181022009, 16807, 2147483647);
            std::shared_ptr<Generator> genB = std::make_shared<Generator>(1233683848, 48271, 2147483647);

            DuelingGeneratorJudge test;
            test.AddGenerator(genA);
            test.AddGenerator(genB);
            // run one round and compare the results
            Assert::AreEqual(true, test.CompareGeneratorOutcomes());
        }

        /*
        */
        TEST_METHOD(December15_CountMatchingResults_AoC_test)
        {
            std::shared_ptr<Generator> genA = std::make_shared<Generator>(65, 16807, 2147483647);
            std::shared_ptr<Generator> genB = std::make_shared<Generator>(8921, 48271, 2147483647);

            DuelingGeneratorJudge test;
            test.AddGenerator(genA);
            test.AddGenerator(genB);
            Assert::AreEqual(1, test.CountMatchingResults(5));
        }
    };
}
