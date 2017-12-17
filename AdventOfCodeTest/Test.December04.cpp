#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December04.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace December04;

namespace AdventOfCodeTest
{
	TEST_CLASS(Test_December04)
	{
	public:
        // -----------------------------------------
        // CheckPassPhrase
        // -----------------------------------------

		/*
		empty string
		*/
		TEST_METHOD(December04_CheckPassPhrase_emptyString)
		{
			PassPhraseCheck test;
			Assert::AreEqual(true, test.CheckPassPhrase(""));
		}

		/*
		single word with repeating elements
		*/
		TEST_METHOD(December04_CheckPassPhrase_singleWord)
		{
			PassPhraseCheck test;
			Assert::AreEqual(true, test.CheckPassPhrase("aabbaaddaaaabbaaddaaaabbaaddaa"));
		}

		/*
		aa bb cc dd ee is valid.
		*/
		TEST_METHOD(December04_AoC_Test1)
		{
			PassPhraseCheck test;
			Assert::AreEqual(true, test.CheckPassPhrase("aa bb cc dd ee"));
		}

		/*
		aa bb cc dd aa is not valid - the word aa appears more than once.
		*/
		TEST_METHOD(December04_AoC_Test2)
		{
			PassPhraseCheck test;
			Assert::AreEqual(false, test.CheckPassPhrase("aa bb cc dd aa"));
		}

		/*
		aa bb cc dd aaa is valid - aa and aaa count as different words.
		*/
		TEST_METHOD(December04_AoC_Test3)
		{
			PassPhraseCheck test;
			Assert::AreEqual(true, test.CheckPassPhrase("aa bb cc dd aaa"));
		}

        // -----------------------------------------
        // CountValidPassPhrases
        // -----------------------------------------

        TEST_METHOD(December04_CountValidPassPhrases_empty)
        {
            PassPhraseCheck test;
            Assert::AreEqual(0, test.CountValidPassPhrases({}));
        }

        TEST_METHOD(December04_CountValidPassPhrases_singleValid)
        {
            PassPhraseCheck test;
            Assert::AreEqual(1, test.CountValidPassPhrases({"aa bb cc"}));
        }

        TEST_METHOD(December04_CountValidPassPhrases_singleInvalid)
        {
            PassPhraseCheck test;
            Assert::AreEqual(0, test.CountValidPassPhrases({ "aa bb cc bb" }));
        }

        TEST_METHOD(December04_CountValidPassPhrases_mixed)
        {
            PassPhraseCheck test;
            Assert::AreEqual(4, test.CountValidPassPhrases({ "test", "", "test test", "bla blubb blub", "xyz abcdef abc abcd x", "abc def abc" }));
        }
    };
}
