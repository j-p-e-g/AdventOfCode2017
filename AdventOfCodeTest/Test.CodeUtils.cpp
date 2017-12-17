#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/CodeUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace CodeUtils;

namespace CodeUtilTest
{
    TEST_CLASS(Test_CodeUtil)
    {
    public:
        // -----------------------------------------
        // Readfile
        // -----------------------------------------
        /*
        Try to read from a nonexisting file.
        */
        TEST_METHOD(CodeUtil_Readfile_NonExistingFile)
        {
            std::stringstream content;
            bool success = CodeUtil::ReadFile("ajsghkjhgkzagkguhskjbh", content);

            Assert::AreEqual(false, success);
            Assert::AreEqual(true, content.str().empty());
        }

        /*
        Try to read from this file (we know it exists)
        TODO: Figure out how to test file reading for unit tests (currently, the file can never be found)
        */
        //TEST_METHOD(CodeUtil_Readfile)
        //{
        //    std::stringstream content;
        //    bool success = CodeUtil::ReadFile("../../Test.CodeUtils.cpp", content);

        //    Assert::AreEqual(true, success);
        //    Assert::AreEqual(false, content.str().empty());
        //}

        // -----------------------------------------
        // SplitStringBySpace
        // -----------------------------------------
        /*
        empty string
        */
        TEST_METHOD(CodeUtil_SplitStringBySpace_empty)
        {
            const std::vector<std::string> vector = CodeUtil::SplitStringBySpace("");

            Assert::AreEqual(true, vector.empty());
        }

        /*
        single (long) word
        */
        TEST_METHOD(CodeUtil_SplitStringBySpace_single)
        {
            const std::vector<std::string> vector = CodeUtil::SplitStringBySpace("aghojukfgvgtshsilhjuioeazgf7tdibhjshjsuiztawuirzfuzvtzwauth3967t94z6oz4ju3gw890z2387r5t378zh");

            Assert::AreEqual(1, static_cast<int>(vector.size()));
            Assert::AreEqual("aghojukfgvgtshsilhjuioeazgf7tdibhjshjsuiztawuirzfuzvtzwauth3967t94z6oz4ju3gw890z2387r5t378zh", vector[0].c_str());
        }

        /*
        several one-char words
        */
        TEST_METHOD(CodeUtil_SplitStringBySpace_shortWords)
        {
            const std::vector<std::string> vector = CodeUtil::SplitStringBySpace("a b c");

            Assert::AreEqual(3, static_cast<int>(vector.size()));
            Assert::AreEqual("a", vector[0].c_str());
            Assert::AreEqual("b", vector[1].c_str());
            Assert::AreEqual("c", vector[2].c_str());
        }

        /*
        several words, separated by tab
        */
        TEST_METHOD(CodeUtil_SplitStringBySpace_tab)
        {
            const std::vector<std::string> vector = CodeUtil::SplitStringBySpace("foobar	blubb");

            Assert::AreEqual(2, static_cast<int>(vector.size()));
            Assert::AreEqual("foobar", vector[0].c_str());
            Assert::AreEqual("blubb", vector[1].c_str());
        }

        /*
        several words, separated by multiple spaces
        */
        TEST_METHOD(CodeUtil_SplitStringBySpace_multiSpace)
        {
            std::vector<std::string> vector = CodeUtil::SplitStringBySpace("xyzzy     baz  bar");

            Assert::AreEqual(3, static_cast<int>(vector.size()));
            Assert::AreEqual("xyzzy", vector[0].c_str());
            Assert::AreEqual("baz", vector[1].c_str());
            Assert::AreEqual("bar", vector[2].c_str());
        }

        /*
        starts with space
        */
        TEST_METHOD(CodeUtil_SplitStringBySpace_startsWithSpace)
        {
            const std::vector<std::string> vector = CodeUtil::SplitStringBySpace("        qwerty");

            Assert::AreEqual(1, static_cast<int>(vector.size()));
            Assert::AreEqual("qwerty", vector[0].c_str());
        }

        /*
        ends with space
        */
        TEST_METHOD(CodeUtil_SplitStringBySpace_endsWithSpace)
        {
            const std::vector<std::string> vector = CodeUtil::SplitStringBySpace("bla test    ");

            Assert::AreEqual(2, static_cast<int>(vector.size()));
            Assert::AreEqual("bla", vector[0].c_str());
            Assert::AreEqual("test", vector[1].c_str());
        }

        // -----------------------------------------------
        // ConvertStringVectorToIntVector
        // -----------------------------------------------
        /*
        empty input
        */
        TEST_METHOD(CodeUtil_ConvertStringVectorToIntVector_empty)
        {
            const std::vector<std::string> input = {};
            std::vector<int> output;
            bool success = CodeUtil::ConvertStringVectorToIntVector(input, output);

            Assert::AreEqual(true, success);
            Assert::AreEqual(true, output.empty());
        }

        /*
        single positive number
        */
        TEST_METHOD(CodeUtil_ConvertStringVectorToIntVector_positiveNumber)
        {
            const std::vector<std::string> input = {"9786"};
            std::vector<int> output;
            bool success = CodeUtil::ConvertStringVectorToIntVector(input, output);

            Assert::AreEqual(true, success);
            Assert::AreEqual(1, static_cast<int>(output.size()));
            Assert::AreEqual(9786, output[0]);
        }

        /*
        single negative number
        */
        TEST_METHOD(CodeUtil_ConvertStringVectorToIntVector_negativeNumber)
        {
            const std::vector<std::string> input = { "-77" };
            std::vector<int> output;
            bool success = CodeUtil::ConvertStringVectorToIntVector(input, output);

            Assert::AreEqual(true, success);
            Assert::AreEqual(1, static_cast<int>(output.size()));
            Assert::AreEqual(-77, output[0]);
        }

        /*
        single non-numerical entry
        */
        TEST_METHOD(CodeUtil_ConvertStringVectorToIntVector_singleNonNumber)
        {
            const std::vector<std::string> input = { "4g" };
            std::vector<int> output;
            bool success = CodeUtil::ConvertStringVectorToIntVector(input, output);

            Assert::AreEqual(false, success);
            Assert::AreEqual(true, output.empty());
        }

        /*
        spaces-only entry
        */
        TEST_METHOD(CodeUtil_ConvertStringVectorToIntVector_spacesOnly)
        {
            const std::vector<std::string> input = { "   " };
            std::vector<int> output;
            bool success = CodeUtil::ConvertStringVectorToIntVector(input, output);

            Assert::AreEqual(false, success);
            Assert::AreEqual(true, output.empty());
        }

        /*
        several numerical entries
        */
        TEST_METHOD(CodeUtil_ConvertStringVectorToIntVector_severalNumbers)
        {
            const std::vector<std::string> input = { "5", "-76", "3128" };
            std::vector<int> output;
            bool success = CodeUtil::ConvertStringVectorToIntVector(input, output);

            Assert::AreEqual(true, success);
            Assert::AreEqual(3, static_cast<int>(output.size()));
            Assert::AreEqual(5, output[0]);
            Assert::AreEqual(-76, output[1]);
            Assert::AreEqual(3128, output[2]);
        }

        /*
        contains a non-numerical entry
        */
        TEST_METHOD(CodeUtil_ConvertStringVectorToIntVector_containsInvalidEntry)
        {
            const std::vector<std::string> input = { "412", "bla", "13" };
            std::vector<int> output;
            bool success = CodeUtil::ConvertStringVectorToIntVector(input, output);

            Assert::AreEqual(false, success);
        }
    };
}
