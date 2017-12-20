#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December11b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December11;

    TEST_CLASS(Test_December11b)
    {
    public:
        // ------------------------------------
        // GetTargetDistanceToOrigin
        // ------------------------------------
        /*
        empty path
        */
        TEST_METHOD(December11b_GetMaxDistanceFromOriginEver_empty)
        {
            InfiniteHexGridB test(std::vector<std::string>({}));
            Assert::AreEqual(0, test.GetMaxDistanceFromOriginEver());
        }

        /*
        the final distance is also the maximum
        */
        TEST_METHOD(December11b_GetMaxDistanceFromOriginEver_finalIsMax)
        {
            InfiniteHexGridB test({ "n", "ne", "n" });
            Assert::AreEqual(3, InfiniteHexGridB::GetTargetDistanceToOrigin(test.GetTargetCell()));
            Assert::AreEqual(3, test.GetMaxDistanceFromOriginEver());
        }

        /*
        the final distance is smaller than the maximum
        */
        TEST_METHOD(December11b_GetMaxDistanceFromOriginEver_finalIsNotMax)
        {
            InfiniteHexGridB test({ "nw", "n", "n", "se", "s" });
            Assert::AreEqual(1, InfiniteHexGridB::GetTargetDistanceToOrigin(test.GetTargetCell()));
            Assert::AreEqual(3, test.GetMaxDistanceFromOriginEver());
        }
    };
}
