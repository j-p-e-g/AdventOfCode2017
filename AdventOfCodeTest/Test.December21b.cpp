#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December21b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December21;

    TEST_CLASS(Test_December21b)
    {
    public:
        // copy tests from 21: they should still work with the changed logic
        TEST_METHOD(December21b_CountActivePixels_empty)
        {
            PixelPatternB test;
            Assert::AreEqual(5, test.CountActivePixels());
        }

        /*
        None of the rules matches.
        */
        TEST_METHOD(December21b_CountActivePixels_noMatches)
        {
            PixelPatternB test;
            Assert::AreEqual(true, test.ParseLine(".#./#../... => ...#/#.../#..#/#..#"));
            Assert::AreEqual(true, test.ParseLine(".#./.#./.#. => .###/##../...#/#.##"));
            Assert::AreEqual(false, test.ProcessRules(1));

            // stays at 5
            Assert::AreEqual(5, test.CountActivePixels());
        }


        /*
        Rule can be applied directly to start pattern
        */
        TEST_METHOD(December21b_CountActivePixels_direct)
        {
            PixelPatternB test;
            Assert::AreEqual(true, test.ParseLine(".#./..#/### => ...#/..#./.#../#..."));
            Assert::AreEqual(true, test.ProcessRules(1));

            Assert::AreEqual(4, test.CountActivePixels());
        }

        /*
        Rule needs to be flipped before it can be applied to the start pattern

        .#.      .#.
        ..#  ->  #..
        ###      ###
        */
        TEST_METHOD(December21b_CountActivePixels_flip)
        {
            PixelPatternB test;
            Assert::AreEqual(true, test.ParseLine(".#./#../### => .#.#/#.#./##.#/#..#"));
            Assert::AreEqual(true, test.ProcessRules(1));

            Assert::AreEqual(9, test.CountActivePixels());
        }

        /*
        Rule needs to be rotated before it can be applied to the start pattern

        .#.      #..
        ..#  ->  #.#
        ###      ##.
        */
        TEST_METHOD(December21b_CountActivePixels_rotate)
        {
            PixelPatternB test;

            Assert::AreEqual(true, test.ParseLine("#../#.#/##. => ..../..#./..../...."));
            Assert::AreEqual(true, test.ProcessRules(1));

            Assert::AreEqual(1, test.CountActivePixels());
        }

        /*
        Rule needs to be flipped and rotated before it can be applied to the start pattern

        .#.      .##      ##.
        ..#  ->  #.#  ->  #.#
        ###      ..#      #..
        */
        TEST_METHOD(December21b_CountActivePixels_flipAndRotate)
        {
            PixelPatternB test;

            Assert::AreEqual(true, test.ParseLine("#../#.#/##. => .##./..../..../.#.."));
            Assert::AreEqual(true, test.ProcessRules(1));

            Assert::AreEqual(3, test.CountActivePixels());
        }

        /*
        Suppose the book contained the following two rules:

        ../.# => ##./#../...
        .#./..#/### => #..#/..../..../#..#

        [...]

        Thus, after 2 iterations, the grid contains 12 pixels that are on.
        */
        TEST_METHOD(December21b_CountActivePixels_AoC_test)
        {
            PixelPatternB test;
            Assert::AreEqual(true, test.ParseLine("../.# => ##./#../..."));
            Assert::AreEqual(true, test.ParseLine(".#./..#/### => #..#/..../..../#..#"));
            Assert::AreEqual(true, test.ProcessRules(2));

            Assert::AreEqual(12, test.CountActivePixels());
        }

        /*
        Puzzle/Solution from part 1
        */
        TEST_METHOD(December21b_CountActivePixels_fileInput)
        {
            AdventOfCode::December21::PixelPatternB test("InputFiles/input21.txt");
            // 5 iterations
            test.ProcessRules(5);
            Assert::AreEqual(188, test.CountActivePixels());
        }
    };
}
