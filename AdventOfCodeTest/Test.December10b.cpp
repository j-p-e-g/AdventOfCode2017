#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December10b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December10;

    TEST_CLASS(Test_December10b)
    {
    public:
        // ------------------------------------
        // ConvertStringToAsciiVector
        // ------------------------------------
        /*
        empty string
        */
        TEST_METHOD(December10b_ConvertStringToAsciiVector_empty)
        {
            std::vector<int> asciiVector;
            ComplexKnotHash::ConvertStringToAsciiVector("", asciiVector);

            Assert::AreEqual(true, asciiVector.empty());
        }

        /*
        3 spaces
        */
        TEST_METHOD(December10b_ConvertStringToAsciiVector_spaces)
        {
            std::vector<int> asciiVector;
            ComplexKnotHash::ConvertStringToAsciiVector("   ", asciiVector);

            Assert::AreEqual(3, static_cast<int>(asciiVector.size()));
            for (const auto& val : asciiVector)
            {
                Assert::AreEqual(32, val);
            }
        }

        /*
        some special characters
        */
        TEST_METHOD(December10b_ConvertStringToAsciiVector_specialChars)
        {
            std::vector<int> asciiVector;
            ComplexKnotHash::ConvertStringToAsciiVector("@&_^", asciiVector);

            Assert::AreEqual(4, static_cast<int>(asciiVector.size()));
            Assert::AreEqual(64, asciiVector[0]);
            Assert::AreEqual(38, asciiVector[1]);
            Assert::AreEqual(95, asciiVector[2]);
            Assert::AreEqual(94, asciiVector[3]);
        }

        /*
        For example, if you are given 1,2,3, you should convert it to the ASCII codes for each character: 49,44,50,44,51.
        */
        TEST_METHOD(December10b_ConvertStringToAsciiVector_AoC_test)
        {
            std::vector<int> asciiVector;
            ComplexKnotHash::ConvertStringToAsciiVector("1,2,3", asciiVector);

            Assert::AreEqual(5, static_cast<int>(asciiVector.size()));
            Assert::AreEqual(49, asciiVector[0]);
            Assert::AreEqual(44, asciiVector[1]);
            Assert::AreEqual(50, asciiVector[2]);
            Assert::AreEqual(44, asciiVector[3]);
            Assert::AreEqual(51, asciiVector[4]);
        }

        // -----------------------------------------
        // ReduceToDenseHash
        // -----------------------------------------
        /*
        length needs to be a multiplier of 16
        */
        TEST_METHOD(December10b_ReduceToDenseHash_invalidLength)
        {
            std::vector<int> inputHash = { 8, 25, 3, 16, 7 };
            std::vector<int> outputHash;

            Assert::AreEqual(false, ComplexKnotHash::ReduceToDenseHash(inputHash, outputHash));
        }

        /*
        length needs to be a multiplier of 16
        */
        TEST_METHOD(December10b_ReduceToDenseHash_validLength)
        {
            std::vector<int> inputHash = { 1, 2, 3, 4, 5, 6, 7, 8,
                                           1, 2, 3, 4, 5, 6, 7, 8,
                                           1, 2, 3, 4, 5, 6, 7, 8,
                                           1, 2, 3, 4, 5, 6, 7, 8 };
            std::vector<int> outputHash;

            Assert::AreEqual(true, ComplexKnotHash::ReduceToDenseHash(inputHash, outputHash));
        }

        /*
        For example, if the first sixteen elements of your sparse hash are as shown below, and the XOR operator is ^, you would calculate the first output number like this:

        65 ^ 27 ^ 9 ^ 1 ^ 4 ^ 3 ^ 40 ^ 50 ^ 91 ^ 7 ^ 6 ^ 0 ^ 2 ^ 5 ^ 68 ^ 22 = 64
        */
        TEST_METHOD(December10b_ReduceToDenseHash_AoC_test)
        {
            const std::vector<int> inputHash = { 65, 27, 9, 1, 4, 3, 40, 50, 91, 7, 6, 0, 2, 5, 68, 22 };
            std::vector<int> outputHash;

            Assert::AreEqual(true, ComplexKnotHash::ReduceToDenseHash(inputHash, outputHash));
            Assert::AreEqual(1, static_cast<int>(outputHash.size()));
            Assert::AreEqual(64, outputHash[0]);
        }

        // -----------------------------------------
        // ConvertVectorToHexValue
        // -----------------------------------------
        /*
        empty vector
        */
        TEST_METHOD(December10b_ConvertVectorToHexValue_empty)
        {
            std::string hexValue;
            ComplexKnotHash::ConvertVectorToHexValue({}, hexValue);
            Assert::AreEqual("", hexValue.c_str());
        }

        /*
        single value that can be expressed in a single hex digit
        */
        TEST_METHOD(December10b_ConvertVectorToHexValue_singleDigit)
        {
            std::string hexValue;
            ComplexKnotHash::ConvertVectorToHexValue({12}, hexValue);
            Assert::AreEqual("0c", hexValue.c_str());
        }

        /*
        single value that requires a double hex digit
        */
        TEST_METHOD(December10b_ConvertVectorToHexValueh_doubleDigit)
        {
            std::string hexValue;
            ComplexKnotHash::ConvertVectorToHexValue({117}, hexValue);
            Assert::AreEqual("75", hexValue.c_str());
        }

        /*
        So, if your first three numbers are 64, 7, 255, they correspond to the hexadecimal numbers 40, 07, ff, and so the first six characters of the hash would be 4007ff.
        */
        TEST_METHOD(December10b_ConvertVectorToHexValue_AoC_test)
        {
            std::string hexValue;
            ComplexKnotHash::ConvertVectorToHexValue({64, 7, 255}, hexValue);
            Assert::AreEqual("4007ff", hexValue.c_str());
        }

        // -----------------------------------------
        // GetKnotHashHexValue
        // -----------------------------------------
        /*
        The empty string becomes a2582a3a0e66e6e86e3812dcb672a272.
        */
        TEST_METHOD(December10b_AoC_test1)
        {
            ComplexKnotHash test;
            test.ParseLine("");
            Assert::AreEqual("a2582a3a0e66e6e86e3812dcb672a272", test.GetKnotHashHexValue().c_str());
        }

        /*
        AoC 2017 becomes 33efeb34ea91902bb2f59c9920caa6cd.
        */
        TEST_METHOD(December10b_AoC_test2)
        {
            ComplexKnotHash test;
            test.ParseLine("AoC 2017");
            Assert::AreEqual("33efeb34ea91902bb2f59c9920caa6cd", test.GetKnotHashHexValue().c_str());
        }

        /*
        1,2,3 becomes 3efbe78a8d82f29979031a4aa0b16a9d.
        */
        TEST_METHOD(December10b_AoC_test3)
        {
            ComplexKnotHash test;
            test.ParseLine("1,2,3");
            Assert::AreEqual("3efbe78a8d82f29979031a4aa0b16a9d", test.GetKnotHashHexValue().c_str());
        }

        /*
        1,2,4 becomes 63960835bcdc130f0b66d7ff4f6a5a8e.
        */
        TEST_METHOD(December10b_AoC_test4)
        {
            ComplexKnotHash test;
            test.ParseLine("1,2,4");
            Assert::AreEqual("63960835bcdc130f0b66d7ff4f6a5a8e", test.GetKnotHashHexValue().c_str());
        }
    };
}
