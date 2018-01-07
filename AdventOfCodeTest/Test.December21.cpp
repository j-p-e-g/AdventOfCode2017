#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December21.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December21;

    TEST_CLASS(Test_December21)
    {
    public:
        // --------------------------------
        // PixelPattern::CreateMatrix
        // --------------------------------
        TEST_METHOD(December21_CreateMatrix_empty)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            Assert::AreEqual(false, PixelPattern::CreateMatrix("", matrix));
        }

        TEST_METHOD(December21_CreateMatrix_uninitialized)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix;
            Assert::AreEqual(false, PixelPattern::CreateMatrix("x/y/z", matrix));
        }

        TEST_METHOD(December21_CreateMatrix)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            Assert::AreEqual(true, PixelPattern::CreateMatrix("abc/de", matrix));
            Assert::AreEqual(2, matrix->GetHeight());
            Assert::AreEqual(3, matrix->GetWidth());

            Assert::AreEqual('a', matrix->Get(0, 0));
            Assert::AreEqual('b', matrix->Get(1, 0));
            Assert::AreEqual('c', matrix->Get(2, 0));
            Assert::AreEqual('d', matrix->Get(0, 1));
            Assert::AreEqual('e', matrix->Get(1, 1));
            Assert::AreEqual(' ', matrix->Get(2, 1));
        }

        // ---------------------------------
        // PixelPattern::ParseLine
        // ---------------------------------
        TEST_METHOD(December21_ParseLine_unexpectedSymbol)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine("##/,, => .../#,#/###"));
        }

        TEST_METHOD(December21_ParseLine_missingInput)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine(" => ##/.."));
        }

        TEST_METHOD(December21_ParseLine_missingOutput)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine(".#/.# =>"));
        }

        TEST_METHOD(December21_ParseLine_missingArrow)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine(".#/#. .../.#./..."));
        }

        TEST_METHOD(December21_ParseLine_extraArrow)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine(".#/#. => .../.#./... => ..##/.#.#/##.#/.###"));
        }

        TEST_METHOD(December21_ParseLine_extraSlashes)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine("#.//#. => ..#/.#./##."));
        }

        TEST_METHOD(December21_ParseLine_inputNotSquare)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine("..#/#.. => .##/#.#/..."));
        }

        TEST_METHOD(December21_ParseLine_outputNotSquare)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine("##/#. => .#/#./.."));
        }

        TEST_METHOD(December21_ParseLine_patternKeepsSize)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine("##/.. => .#/#."));
        }

        TEST_METHOD(December21_ParseLine_patternShrinks)
        {
            PixelPattern test;
            Assert::AreEqual(false, test.ParseLine("###/.../..# => ##/.."));
        }

        TEST_METHOD(December21_ParseLine_2x2)
        {
            PixelPattern test;
            Assert::AreEqual(true, test.ParseLine("##/.. => ###/.../..#"));
        }

        TEST_METHOD(December21_ParseLine_3x3)
        {
            PixelPattern test;
            Assert::AreEqual(true, test.ParseLine("#.#/#../..# => #.##/#.../###./#..#"));
        }

        // --------------------------------
        // PixelPattern::SplitMatrix
        // --------------------------------
        TEST_METHOD(December21_SplitMatrix_2x2_attempt3)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("../##", matrix);

            // wrong size
            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            Assert::AreEqual(false, PixelPattern::SplitMatrix(matrix, 3, subMatrices));
        }

        TEST_METHOD(December21_SplitMatrix2x2)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("../##", matrix);

            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            Assert::AreEqual(true, PixelPattern::SplitMatrix(matrix, 2, subMatrices));

            // equal to the initial matrix
            Assert::AreEqual(1, static_cast<int>(subMatrices.size()));
            Assert::AreEqual(true, subMatrices.begin()->first == CodeUtils::Point(0,0));

            Assert::AreEqual(2, subMatrices.begin()->second->GetWidth());
            Assert::AreEqual(2, subMatrices.begin()->second->GetHeight());

            Assert::AreEqual('.', subMatrices.begin()->second->Get(0, 0));
            Assert::AreEqual('.', subMatrices.begin()->second->Get(1, 0));
            Assert::AreEqual('#', subMatrices.begin()->second->Get(0, 1));
            Assert::AreEqual('#', subMatrices.begin()->second->Get(1, 1));
        }

        TEST_METHOD(December21_SplitMatrix_3x3_attempt2)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix(".#./.##/..#", matrix);

            // wrong size
            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            Assert::AreEqual(false, PixelPattern::SplitMatrix(matrix, 2, subMatrices));
        }

        TEST_METHOD(December21_SplitMatrix3x3)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix(".#./.##/..#", matrix);

            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            Assert::AreEqual(true, PixelPattern::SplitMatrix(matrix, 3, subMatrices));

            // equal to the initial matrix
            Assert::AreEqual(1, static_cast<int>(subMatrices.size()));

            Assert::AreEqual(3, subMatrices.begin()->second->GetWidth());
            Assert::AreEqual(3, subMatrices.begin()->second->GetHeight());
            Assert::AreEqual('.', subMatrices.begin()->second->Get(0, 0));
            Assert::AreEqual('#', subMatrices.begin()->second->Get(1, 0));
            Assert::AreEqual('.', subMatrices.begin()->second->Get(2, 0));
            Assert::AreEqual('.', subMatrices.begin()->second->Get(0, 1));
            Assert::AreEqual('#', subMatrices.begin()->second->Get(1, 1));
            Assert::AreEqual('#', subMatrices.begin()->second->Get(2, 1));
            Assert::AreEqual('.', subMatrices.begin()->second->Get(0, 2));
            Assert::AreEqual('.', subMatrices.begin()->second->Get(1, 2));
            Assert::AreEqual('#', subMatrices.begin()->second->Get(2, 2));
        }

        /*
        split up into 4 2x2 sub-matrices

          ..##
          ..##  ->  ..  ##  #.  .#
          #..#      ..  ##  #.  .#
          #..#
        */
        TEST_METHOD(December21_SplitMatrix4x4)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("..##/..##/#..#/#..#", matrix);

            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            Assert::AreEqual(true, PixelPattern::SplitMatrix(matrix, 2, subMatrices));

            // split into 4 matrices
            Assert::AreEqual(4, static_cast<int>(subMatrices.size()));

            const auto found00 = subMatrices.find(CodeUtils::Point(0, 0));
            const auto found10 = subMatrices.find(CodeUtils::Point(1, 0));
            const auto found01 = subMatrices.find(CodeUtils::Point(0, 1));
            const auto found11 = subMatrices.find(CodeUtils::Point(1, 1));
            Assert::AreEqual(false, found00 == subMatrices.end());
            Assert::AreEqual(false, found10 == subMatrices.end());
            Assert::AreEqual(false, found01 == subMatrices.end());
            Assert::AreEqual(false, found11 == subMatrices.end());

            Assert::AreEqual(2, found00->second->GetWidth());
            Assert::AreEqual(2, found00->second->GetHeight());
            Assert::AreEqual('.', found00->second->Get(0, 0));
            Assert::AreEqual('.', found00->second->Get(1, 0));
            Assert::AreEqual('.', found00->second->Get(0, 1));
            Assert::AreEqual('.', found00->second->Get(1, 1));

            Assert::AreEqual(2, found10->second->GetWidth());
            Assert::AreEqual(2, found10->second->GetHeight());
            Assert::AreEqual('#', found10->second->Get(0, 0));
            Assert::AreEqual('#', found10->second->Get(1, 0));
            Assert::AreEqual('#', found10->second->Get(0, 1));
            Assert::AreEqual('#', found10->second->Get(1, 1));

            Assert::AreEqual(2, found01->second->GetWidth());
            Assert::AreEqual(2, found01->second->GetHeight());
            Assert::AreEqual('#', found01->second->Get(0, 0));
            Assert::AreEqual('.', found01->second->Get(1, 0));
            Assert::AreEqual('#', found01->second->Get(0, 1));
            Assert::AreEqual('.', found01->second->Get(1, 1));

            Assert::AreEqual(2, found11->second->GetWidth());
            Assert::AreEqual(2, found11->second->GetHeight());
            Assert::AreEqual('.', found11->second->Get(0, 0));
            Assert::AreEqual('#', found11->second->Get(1, 0));
            Assert::AreEqual('.', found11->second->Get(0, 1));
            Assert::AreEqual('#', found11->second->Get(1, 1));
        }

        /*
        split up into 9 2x2 sub-matrices

        ..##..
        ..#..#      ..  ##  ..  #.  ..  .#  #.  ##  #.
        #....#  ->  ..  #.  .#  ##  #.  .#  ##  ..  .#
        ###..#      
        #.###.
        ##...#
        */
        TEST_METHOD(December21_SplitMatrix6x6)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("..##../..#..#/#....#/###..#/#.###./##...#", matrix);

            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            Assert::AreEqual(true, PixelPattern::SplitMatrix(matrix, 2, subMatrices));

            // split into 9 matrices
            Assert::AreEqual(9, static_cast<int>(subMatrices.size()));
            const auto found00 = subMatrices.find(CodeUtils::Point(0, 0));
            const auto found10 = subMatrices.find(CodeUtils::Point(1, 0));
            const auto found20 = subMatrices.find(CodeUtils::Point(2, 0));
            const auto found01 = subMatrices.find(CodeUtils::Point(0, 1));
            const auto found11 = subMatrices.find(CodeUtils::Point(1, 1));
            const auto found21 = subMatrices.find(CodeUtils::Point(2, 1));
            const auto found02 = subMatrices.find(CodeUtils::Point(0, 2));
            const auto found12 = subMatrices.find(CodeUtils::Point(1, 2));
            const auto found22 = subMatrices.find(CodeUtils::Point(2, 2));

            Assert::AreEqual(false, found00 == subMatrices.end());
            Assert::AreEqual(false, found10 == subMatrices.end());
            Assert::AreEqual(false, found20 == subMatrices.end());
            Assert::AreEqual(false, found01 == subMatrices.end());
            Assert::AreEqual(false, found11 == subMatrices.end());
            Assert::AreEqual(false, found21 == subMatrices.end());
            Assert::AreEqual(false, found02 == subMatrices.end());
            Assert::AreEqual(false, found12 == subMatrices.end());
            Assert::AreEqual(false, found22 == subMatrices.end());

            // just do some spot checks
            Assert::AreEqual(2, found10->second->GetWidth());
            Assert::AreEqual(2, found20->second->GetHeight());
            Assert::AreEqual(2, found01->second->GetWidth());
            Assert::AreEqual(2, found21->second->GetHeight());
            Assert::AreEqual(2, found02->second->GetWidth());
            Assert::AreEqual(2, found22->second->GetHeight());

            //..#..#      ..  ##  ..  #.  ..  .#  #.  ##  #.
            //#....#  ->  ..  #.  .#  ##  #.  .#  ##  ..  .#
            Assert::AreEqual('.', found00->second->Get(0, 1));
            Assert::AreEqual('#', found10->second->Get(1, 0));
            Assert::AreEqual('.', found20->second->Get(1, 0));
            Assert::AreEqual('#', found01->second->Get(0, 0));
            Assert::AreEqual('.', found11->second->Get(1, 0));
            Assert::AreEqual('#', found21->second->Get(1, 1));
            Assert::AreEqual('#', found02->second->Get(0, 1));
            Assert::AreEqual('.', found12->second->Get(1, 1));
            Assert::AreEqual('.', found22->second->Get(0, 1));
        }

        // -----------------------------------------
        // PixelPattern::ApplyRulesToSubMatrix
        // -----------------------------------------
        TEST_METHOD(December21_ApplyRulesToSubMatrix_ruleNotFound)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix(".#/##", matrix);

            PixelPattern test;
            Assert::AreEqual(false, test.ApplyRulesToSubMatrix(matrix));
        }

        TEST_METHOD(December21_ApplyRulesToSubMatrix_2x2)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix(".#/##", matrix);

            PixelPattern test;
            // 2nd rule matches
            Assert::AreEqual(true, test.ParseLine("../## => .#./###/..."));
            Assert::AreEqual(true, test.ParseLine(".#/## => ..#/#.#/#.."));
            Assert::AreEqual(true, test.ApplyRulesToSubMatrix(matrix));

            // should be the pattern outcome
            Assert::AreEqual(3, matrix->GetWidth());
            Assert::AreEqual(3, matrix->GetHeight());

            Assert::AreEqual('.', matrix->Get(0, 0));
            Assert::AreEqual('.', matrix->Get(1, 0));
            Assert::AreEqual('#', matrix->Get(2, 0));
            Assert::AreEqual('#', matrix->Get(0, 1));
            Assert::AreEqual('.', matrix->Get(1, 1));
            Assert::AreEqual('#', matrix->Get(2, 1));
            Assert::AreEqual('#', matrix->Get(0, 2));
            Assert::AreEqual('.', matrix->Get(1, 2));
            Assert::AreEqual('.', matrix->Get(2, 2));
        }

        TEST_METHOD(December21_ApplyRulesToSubMatrix_3x3)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("##./#.#/..#", matrix);

            PixelPattern test;
            Assert::AreEqual(true, test.ParseLine("##./#.#/..# => #..#/#..#/##../..##"));
            Assert::AreEqual(true, test.ApplyRulesToSubMatrix(matrix));

            // should be the pattern outcome
            Assert::AreEqual(4, matrix->GetWidth());
            Assert::AreEqual(4, matrix->GetHeight());

            Assert::AreEqual('#', matrix->Get(0, 0));
            Assert::AreEqual('.', matrix->Get(1, 0));
            Assert::AreEqual('.', matrix->Get(2, 0));
            Assert::AreEqual('#', matrix->Get(3, 0));
            Assert::AreEqual('#', matrix->Get(0, 1));
            Assert::AreEqual('.', matrix->Get(1, 1));
            Assert::AreEqual('.', matrix->Get(2, 1));
            Assert::AreEqual('#', matrix->Get(3, 1));
            Assert::AreEqual('#', matrix->Get(0, 2));
            Assert::AreEqual('#', matrix->Get(1, 2));
            Assert::AreEqual('.', matrix->Get(2, 2));
            Assert::AreEqual('.', matrix->Get(3, 2));
            Assert::AreEqual('.', matrix->Get(0, 3));
            Assert::AreEqual('.', matrix->Get(1, 3));
            Assert::AreEqual('#', matrix->Get(2, 3));
            Assert::AreEqual('#', matrix->Get(3, 3));
        }

        TEST_METHOD(December21_ApplyRulesToSubMatrix_2x2_flip)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix(".#/.#", matrix);

            PixelPattern test;
            // needs to be flipped
            //  .# -> #.
            //  .#    #.
            Assert::AreEqual(true, test.ParseLine("#./#. => #.#/###/#.."));
            Assert::AreEqual(true, test.ApplyRulesToSubMatrix(matrix));

            // should be the pattern outcome
            Assert::AreEqual(3, matrix->GetWidth());
            Assert::AreEqual(3, matrix->GetHeight());

            Assert::AreEqual('#', matrix->Get(0, 0));
            Assert::AreEqual('.', matrix->Get(1, 0));
            Assert::AreEqual('#', matrix->Get(2, 0));
            Assert::AreEqual('#', matrix->Get(0, 1));
            Assert::AreEqual('#', matrix->Get(1, 1));
            Assert::AreEqual('#', matrix->Get(2, 1));
            Assert::AreEqual('#', matrix->Get(0, 2));
            Assert::AreEqual('.', matrix->Get(1, 2));
            Assert::AreEqual('.', matrix->Get(2, 2));
        }

        TEST_METHOD(December21_ApplyRulesToSubMatrix_3x3_rotate)
        {
            std::shared_ptr<Matrix::CharMatrix> matrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix(".##/..#/.##", matrix);

            PixelPattern test;
            // needs to be rotated
            // .##    ###
            // ..# -> #.#
            // .##    ...
            Assert::AreEqual(true, test.ParseLine("###/#.#/... => #.##/#..#/#.#./##.."));
            Assert::AreEqual(true, test.ApplyRulesToSubMatrix(matrix));

            // should be the pattern outcome
            Assert::AreEqual(4, matrix->GetWidth());
            Assert::AreEqual(4, matrix->GetHeight());

            Assert::AreEqual('#', matrix->Get(0, 0));
            Assert::AreEqual('.', matrix->Get(1, 0));
            Assert::AreEqual('#', matrix->Get(2, 0));
            Assert::AreEqual('#', matrix->Get(3, 0));
            Assert::AreEqual('#', matrix->Get(0, 1));
            Assert::AreEqual('.', matrix->Get(1, 1));
            Assert::AreEqual('.', matrix->Get(2, 1));
            Assert::AreEqual('#', matrix->Get(3, 1));
            Assert::AreEqual('#', matrix->Get(0, 2));
            Assert::AreEqual('.', matrix->Get(1, 2));
            Assert::AreEqual('#', matrix->Get(2, 2));
            Assert::AreEqual('.', matrix->Get(3, 2));
            Assert::AreEqual('#', matrix->Get(0, 3));
            Assert::AreEqual('#', matrix->Get(1, 3));
            Assert::AreEqual('.', matrix->Get(2, 3));
            Assert::AreEqual('.', matrix->Get(3, 3));
        }

        // --------------------------------
        // PixelPattern::CombineMatrices
        // --------------------------------
        TEST_METHOD(December21_CombineMatrices_4x4)
        {
            std::shared_ptr<Matrix::CharMatrix> expectedMatrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("..##/##../#..#/.##.", expectedMatrix);

            std::shared_ptr<Matrix::CharMatrix> matrix1 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix2 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix3 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix4 = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("../##", matrix1);
            PixelPattern::CreateMatrix("##/..", matrix2);
            PixelPattern::CreateMatrix("#./.#", matrix3);
            PixelPattern::CreateMatrix(".#/#.", matrix4);

            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            subMatrices.emplace(CodeUtils::Point(0, 0), matrix1);
            subMatrices.emplace(CodeUtils::Point(1, 0), matrix2);
            subMatrices.emplace(CodeUtils::Point(0, 1), matrix3);
            subMatrices.emplace(CodeUtils::Point(1, 1), matrix4);

            std::shared_ptr<Matrix::CharMatrix> combinedMatrix = std::make_shared<Matrix::CharMatrix>();
            Assert::AreEqual(true, PixelPattern::CombineMatrices(subMatrices, combinedMatrix));
            Assert::AreEqual(true, expectedMatrix->Equals(*combinedMatrix));
        }

        TEST_METHOD(December21_CombineMatrices_6x6)
        {
            std::shared_ptr<Matrix::CharMatrix> expectedMatrix = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("..##../##..../.##..#/##.##./#.#.##/######", expectedMatrix);

            std::shared_ptr<Matrix::CharMatrix> matrix1 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix2 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix3 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix4 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix5 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix6 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix7 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix8 = std::make_shared<Matrix::CharMatrix>();
            std::shared_ptr<Matrix::CharMatrix> matrix9 = std::make_shared<Matrix::CharMatrix>();
            PixelPattern::CreateMatrix("../##", matrix1);
            PixelPattern::CreateMatrix("##/..", matrix2);
            PixelPattern::CreateMatrix("../..", matrix3);
            PixelPattern::CreateMatrix(".#/##", matrix4);
            PixelPattern::CreateMatrix("#./.#", matrix5);
            PixelPattern::CreateMatrix(".#/#.", matrix6);
            PixelPattern::CreateMatrix("#./##", matrix7);
            PixelPattern::CreateMatrix("#./##", matrix8);
            PixelPattern::CreateMatrix("##/##", matrix9);

            std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
            subMatrices.emplace(CodeUtils::Point(0, 0), matrix1);
            subMatrices.emplace(CodeUtils::Point(1, 0), matrix2);
            subMatrices.emplace(CodeUtils::Point(2, 0), matrix3);
            subMatrices.emplace(CodeUtils::Point(0, 1), matrix4);
            subMatrices.emplace(CodeUtils::Point(1, 1), matrix5);
            subMatrices.emplace(CodeUtils::Point(2, 1), matrix6);
            subMatrices.emplace(CodeUtils::Point(0, 2), matrix7);
            subMatrices.emplace(CodeUtils::Point(1, 2), matrix8);
            subMatrices.emplace(CodeUtils::Point(2, 2), matrix9);

            std::shared_ptr<Matrix::CharMatrix> combinedMatrix = std::make_shared<Matrix::CharMatrix>();
            Assert::AreEqual(true, PixelPattern::CombineMatrices(subMatrices, combinedMatrix));
            Assert::AreEqual(true, expectedMatrix->Equals(*combinedMatrix));
        }

        // ----------------------------------
        // PixelPattern::CountActivePixels
        // ----------------------------------
        /*
        No processing, just count the pixels in the start pattern.

            .#.
            ..#
            ###
        */
        TEST_METHOD(December21_CountActivePixels_empty)
        {
            PixelPattern test;
            Assert::AreEqual(5, test.CountActivePixels());
        }

        /*
        None of the rules matches.
        */
        TEST_METHOD(December21_CountActivePixels_noMatches)
        {
            PixelPattern test;
            Assert::AreEqual(true, test.ParseLine(".#./#../... => ...#/#.../#..#/#..#"));
            Assert::AreEqual(true, test.ParseLine(".#./.#./.#. => .###/##../...#/#.##"));
            Assert::AreEqual(false, test.ProcessRules(1));

            // stays at 5
            Assert::AreEqual(5, test.CountActivePixels());
        }


        /*
        Rule can be applied directly to start pattern
        */
        TEST_METHOD(December21_CountActivePixels_direct)
        {
            PixelPattern test;
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
        TEST_METHOD(December21_CountActivePixels_flip)
        {
            PixelPattern test;
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
        TEST_METHOD(December21_CountActivePixels_rotate)
        {
            PixelPattern test;

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
        TEST_METHOD(December21_CountActivePixels_flipAndRotate)
        {
            PixelPattern test;

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
        TEST_METHOD(December21_CountActivePixels_AoC_test)
        {
            PixelPattern test;
            Assert::AreEqual(true, test.ParseLine("../.# => ##./#../..."));
            Assert::AreEqual(true, test.ParseLine(".#./..#/### => #..#/..../..../#..#"));
            Assert::AreEqual(true, test.ProcessRules(2));

            Assert::AreEqual(12, test.CountActivePixels());
        }
    };
}
