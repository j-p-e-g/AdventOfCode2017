#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December23b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December23;

    TEST_CLASS(Test_December23b)
    {
    public:
        TEST_METHOD(December23b_CalculatePrimesUpToValue_10)
        {
            SimplifiedRegisterHandlerB test;
            std::vector<int> primes;
            test.CalculatePrimesUpToValue(10, primes);

            const std::vector<int> expectedPrimes = { 2, 3, 5, 7 };
            Assert::AreEqual(expectedPrimes.size(), primes.size());
            for (int k = 0; k < expectedPrimes.size(); k++)
            {
                Assert::AreEqual(expectedPrimes[k], primes[k]);
            }
        }

        TEST_METHOD(December23b_CalculatePrimesUpToValue_50)
        {
            SimplifiedRegisterHandlerB test;
            std::vector<int> primes;
            test.CalculatePrimesUpToValue(50, primes);

            const std::vector<int> expectedPrimes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
            Assert::AreEqual(expectedPrimes.size(), primes.size());
            for (int k = 0; k < expectedPrimes.size(); k++)
            {
                Assert::AreEqual(expectedPrimes[k], primes[k]);
            }
        }

        /*
         count non-prime values between 10 and 30 in increases of 1
         primes up to 30: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29
         -> non-primes between 10 and 30: 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26, 27, 28, 30
        */
        TEST_METHOD(December23b_CountNonPrimes_Step1)
        {
            SimplifiedRegisterHandlerB test;
            Assert::AreEqual(15, test.CountNonPrimes(10, 30, 1));
        }

        /*
        count non-prime values between 50 and 100 in increases of 3
        primes up to 100: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 57, 71, 73, 79, 83, 89, 97
        -> non-primes between 50 and 100: 50, 56, 62, 65, 68, 74, 77, 80, 86, 92, 95, 100
        */
        TEST_METHOD(December23b_CountNonPrimes_Step3)
        {
            SimplifiedRegisterHandlerB test;
            Assert::AreEqual(12, test.CountNonPrimes(50, 100, 3));
        }
    };
}
