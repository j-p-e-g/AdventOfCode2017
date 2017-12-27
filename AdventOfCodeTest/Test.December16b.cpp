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

    };
}
