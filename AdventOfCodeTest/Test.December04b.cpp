#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December04b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December04;

    TEST_CLASS(Test_December04b)
    {
    public:
        // ------------------------------------
        // SortLettersInString
        // ------------------------------------
        TEST_METHOD(December04b_SortLettersInString_empty)
        {
            Assert::AreEqual("", AnagramPassPhraseCheck::SortLettersInString("").c_str());
        }

        TEST_METHOD(December04b_SortLettersInString_allSame)
        {
            Assert::AreEqual("zzzzz", AnagramPassPhraseCheck::SortLettersInString("zzzzz").c_str());
        }

        TEST_METHOD(December04b_SortLettersInString_sort)
        {
            Assert::AreEqual("abfgsz", AnagramPassPhraseCheck::SortLettersInString("bzsfga").c_str());
        }

        TEST_METHOD(December04b_SortLettersInString_sortWithDuplicates)
        {
            Assert::AreEqual("aabbccd", AnagramPassPhraseCheck::SortLettersInString("aaccdbb").c_str());
        }

        // ------------------------------------
        // CheckPassPhrase
        // ------------------------------------
        /*
        abcde xyz ecdab is not valid - the letters from the third word can be rearranged to form the first word.
        */
        TEST_METHOD(December04b_AoC_valid)
        {
            AnagramPassPhraseCheck test;
            Assert::AreEqual(false, test.CheckPassPhrase("abcde xyz ecdab"));
        }

        /*
        a ab abc abd abf abj is a valid passphrase, because all letters need to be used when forming another word.
        */
        TEST_METHOD(December04b_AoC_invalid)
        {
            AnagramPassPhraseCheck test;
            Assert::AreEqual(true, test.CheckPassPhrase( "a ab abc abd abf abj" ));
        }
    };
}
