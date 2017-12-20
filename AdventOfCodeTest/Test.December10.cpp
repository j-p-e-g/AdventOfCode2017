#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December10.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December10;

    TEST_CLASS(Test_December10)
	{
	public:
        // -------------------------------
        // InvertSubList
        // -------------------------------
        /*
        inverting a sublist of length 1 or below has no effect
        */
        TEST_METHOD(December10_InvertSubList_single)
        {
            std::vector<int> numbers = { 2, 5, 7 };
            KnotHash::InvertSubList(numbers, 2, 1);

            // same
            Assert::AreEqual(3, static_cast<int>(numbers.size()));
            Assert::AreEqual(2, numbers[0]);
            Assert::AreEqual(5, numbers[1]);
            Assert::AreEqual(7, numbers[2]);
        }

        /*
        inverting the entire list
        */
        TEST_METHOD(December10_InvertSubList_entire)
        {
            std::vector<int> numbers = { 17, -3, 5, 8, 2 };
            KnotHash::InvertSubList(numbers, 0, 5);

            Assert::AreEqual(5, static_cast<int>(numbers.size()));
            // inverted
            Assert::AreEqual(2, numbers[0]);
            Assert::AreEqual(8, numbers[1]);
            Assert::AreEqual(5, numbers[2]);
            Assert::AreEqual(-3, numbers[3]);
            Assert::AreEqual(17, numbers[4]);
        }

        /*
        inverting a sublist (odd number of elements)
        */
        TEST_METHOD(December10_InvertSubList_sublist_odd)
        {
            std::vector<int> numbers = { 2, 8, 62, 13, 12};
            KnotHash::InvertSubList(numbers, 1, 3);

            Assert::AreEqual(5, static_cast<int>(numbers.size()));
            // same
            Assert::AreEqual(2, numbers[0]);
            // inverted
            Assert::AreEqual(13, numbers[1]);
            Assert::AreEqual(62, numbers[2]);
            Assert::AreEqual(8, numbers[3]);
            // same
            Assert::AreEqual(12, numbers[4]);
        }

        /*
        inverting a sublist (even number of elements)
        */
        TEST_METHOD(December10_InvertSubList_sublist_even)
        {
            std::vector<int> numbers = { 7, 29, -3, -5, 1, 16 };
            KnotHash::InvertSubList(numbers, 2, 4);

            Assert::AreEqual(6, static_cast<int>(numbers.size()));
            // same
            Assert::AreEqual(7, numbers[0]);
            Assert::AreEqual(29, numbers[1]);
            // inverted
            Assert::AreEqual(16, numbers[2]);
            Assert::AreEqual(1, numbers[3]);
            Assert::AreEqual(-5, numbers[4]);
            Assert::AreEqual(-3, numbers[5]);
        }

        /*
        inverting the entire list with a wrap around: 3) (4 8 9  becomes  4) (3 9 8
        */
        TEST_METHOD(December10_InvertSubList_entire_wrap)
        {
            std::vector<int> numbers = { 3, 4, 8, 9 };
            KnotHash::InvertSubList(numbers, 1, 4);

            Assert::AreEqual(4, static_cast<int>(numbers.size()));
            Assert::AreEqual(4, numbers[0]);
            Assert::AreEqual(3, numbers[1]);
            Assert::AreEqual(9, numbers[2]);
            Assert::AreEqual(8, numbers[3]);
        }

        /*
        inverting a sublist with a wrap around: 1) 10 11 (100  becomes  100) 10 11 (1
        */
        TEST_METHOD(December10_InvertSubList_sublist_wrap)
        {
            std::vector<int> numbers = { 1, 10, 11, 100 };
            KnotHash::InvertSubList(numbers, 3, 2);

            Assert::AreEqual(4, static_cast<int>(numbers.size()));
            // inverted
            Assert::AreEqual(100, numbers[0]);
            // same
            Assert::AreEqual(10, numbers[1]);
            Assert::AreEqual(11, numbers[2]);
            // inverted
            Assert::AreEqual(1, numbers[3]);
        }

        // ----------------------------
        // AoC samples
        // ----------------------------
        /*
        The first length, 3, selects ([0] 1 2) 3 4 (where parentheses indicate the sublist to be reversed).
        After reversing that section (0 1 2 into 2 1 0), we get ([2] 1 0) 3 4.
        */
        TEST_METHOD(December10_AoC_InvertSubList_base)
        {
            std::vector<int> numbers = { 0, 1, 2, 3, 4 };
            KnotHash::InvertSubList(numbers, 0, 3);
            Assert::AreEqual(5, static_cast<int>(numbers.size()));
            // inverted
            Assert::AreEqual(2, numbers[0]);
            Assert::AreEqual(1, numbers[1]);
            Assert::AreEqual(0, numbers[2]);
            // same
            Assert::AreEqual(3, numbers[3]);
            Assert::AreEqual(4, numbers[4]);
        }
       
        /*
        The second length, 4, selects a section which wraps: 2 1) 0 ([3] 4.
        The sublist 3 4 2 1 is reversed to form 1 2 4 3: 4 3) 0 ([1] 2.
        */
        TEST_METHOD(December10_AoC_InvertSubList_wrapAround)
        {
            std::vector<int> numbers = { 2, 1, 0, 3, 4 };
            KnotHash::InvertSubList(numbers, 3, 4);
            Assert::AreEqual(5, static_cast<int>(numbers.size()));
            // inverted
            Assert::AreEqual(4, numbers[0]);
            Assert::AreEqual(3, numbers[1]);
            // same
            Assert::AreEqual(0, numbers[2]);
            // inverted
            Assert::AreEqual(1, numbers[3]);
            Assert::AreEqual(2, numbers[4]);
        }

        /*
        The third length, 1, selects a sublist of a single element, and so reversing it has no effect.
        */
        TEST_METHOD(December10_AoC_InvertSubList_lengthOne)
        {
            std::vector<int> numbers = { 4, 3, 0, 1, 2 };
            KnotHash::InvertSubList(numbers, 4, 1);
            Assert::AreEqual(5, static_cast<int>(numbers.size()));
            // same
            Assert::AreEqual(4, numbers[0]);
            Assert::AreEqual(3, numbers[1]);
            Assert::AreEqual(0, numbers[2]);
            Assert::AreEqual(1, numbers[3]);
            Assert::AreEqual(2, numbers[4]);
        }

        /*
        The fourth length, 5, selects every element starting with the second: 4) ([3] 0 1 2. Reversing this sublist (3 0 1 2 4 into 4 2 1 0 3) produces: 3) ([4] 2 1 0.
        */
        TEST_METHOD(December10_AoC_InvertSubList_wrapAround_entireList)
        {
            std::vector<int> numbers = { 4, 3, 0, 1, 2 };
            KnotHash::InvertSubList(numbers, 1, 5);
            Assert::AreEqual(5, static_cast<int>(numbers.size()));
            // inverted
            Assert::AreEqual(3, numbers[0]);
            Assert::AreEqual(4, numbers[1]);
            Assert::AreEqual(2, numbers[2]);
            Assert::AreEqual(1, numbers[3]);
            Assert::AreEqual(0, numbers[4]);
        }

        /*
        Suppose we instead only had a circular list containing five elements, 0, 1, 2, 3, 4, and were given input lengths of 3, 4, 1, 5.

        The list begins as [0] 1 2 3 4 (where square brackets indicate the current position).
        The first length, 3, selects ([0] 1 2) 3 4 (where parentheses indicate the sublist to be reversed).
        After reversing that section (0 1 2 into 2 1 0), we get ([2] 1 0) 3 4.
        Then, the current position moves forward by the length, 3, plus the skip size, 0: 2 1 0 [3] 4. Finally, the skip size increases to 1.

        The second length, 4, selects a section which wraps: 2 1) 0 ([3] 4.
        The sublist 3 4 2 1 is reversed to form 1 2 4 3: 4 3) 0 ([1] 2.
        The current position moves forward by the length plus the skip size, a total of 5, causing it not to move because it wraps around: 4 3 0 [1] 2. The skip size increases to 2.

        The third length, 1, selects a sublist of a single element, and so reversing it has no effect.
        The current position moves forward by the length (1) plus the skip size (2): 4 [3] 0 1 2. The skip size increases to 3.

        The fourth length, 5, selects every element starting with the second: 4) ([3] 0 1 2. Reversing this sublist (3 0 1 2 4 into 4 2 1 0 3) produces: 3) ([4] 2 1 0.
        Finally, the current position moves forward by 8: 3 4 2 1 [0]. The skip size increases to 4.

        In this example, the first two numbers in the list end up being 3 and 4; to check the process, you can multiply them together to produce 12.
        */
		TEST_METHOD(December10_AoC_test)
		{
			KnotHash test(5);
            test.ApplyInput({ 3, 4, 1, 5 });
			Assert::AreEqual(12, test.GetCheckSum());
		}
	};
}
