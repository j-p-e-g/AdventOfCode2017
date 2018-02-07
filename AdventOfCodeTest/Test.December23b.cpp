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

        /*
        If the target value is a prime number itself, it needs to be included in the returned list.
        */
        TEST_METHOD(December23b_CalculatePrimesUpToValue_11)
        {
            SimplifiedRegisterHandlerB test;
            std::vector<int> primes;
            test.CalculatePrimesUpToValue(11, primes);

            const std::vector<int> expectedPrimes = { 2, 3, 5, 7, 11 };
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

        /*
        count non-prime values between 20 and 50 in increases of -7
        primes up to 50: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
        -> non-primes between 20 and 50: 50, 36, 22
        */
        TEST_METHOD(December23b_CountNonPrimes_negativeStep)
        {
            SimplifiedRegisterHandlerB test;
            Assert::AreEqual(3, test.CountNonPrimes(50, 20, -7));
        }

        /*
        step of 0 should not result in an infinite loop
        */
        TEST_METHOD(December23b_CountNonPrimes_step0)
        {
            SimplifiedRegisterHandlerB test;
            Assert::AreEqual(-1, test.CountNonPrimes(8, 25, 0));
        }

        /*
        step increasing the value in the wrong direction results in a count of 0
        */
        TEST_METHOD(December23b_CountNonPrimes_oppositeStep)
        {
            SimplifiedRegisterHandlerB test;
            Assert::AreEqual(0, test.CountNonPrimes(10, 50, -3));
        }

        /*
        if start and target are the same, the counter is only increased once
        */
        TEST_METHOD(December23b_CountNonPrimes_identicalNonPrime)
        {
            SimplifiedRegisterHandlerB test;
            Assert::AreEqual(1, test.CountNonPrimes(30, 30, 7));
        }

        /*
        if start and target are the same and prime, the counter never is increased
        */
        TEST_METHOD(December23b_CountNonPrimes_identicalPrime)
        {
            SimplifiedRegisterHandlerB test;
            Assert::AreEqual(0, test.CountNonPrimes(17, 17, -2));
        }
    };
}
