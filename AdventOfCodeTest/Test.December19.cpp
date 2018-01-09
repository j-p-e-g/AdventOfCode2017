#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December19.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December19;

    TEST_CLASS(Test_December19)
    {
    public:
        // -------------------------------------
        // NetworkDiagram
        // -------------------------------------
        TEST_METHOD(December19_ParseLine_empty)
        {
            NetworkDiagram test;
            Assert::AreEqual(true, test.ParseLine(""));
        }

        /*
        expected symbols: +|-, uppercase letters and space
        */
        TEST_METHOD(December19_ParseLine_valid)
        {
            NetworkDiagram test;
            Assert::AreEqual(true, test.ParseLine(" +--C--+ |G +--L"));
        }

        /*
        any other symbol is invalid
        */
        TEST_METHOD(December19_ParseLine_invalid)
        {
            NetworkDiagram test;
            Assert::AreEqual(false, test.ParseLine("&"));
            Assert::AreEqual(false, test.ParseLine("g--"));
            Assert::AreEqual(false, test.ParseLine(" 7"));
        }

        /*
        Ensure that there's exactly one | symbol (and nothing else) in the top row
        */
        TEST_METHOD(December19_IsValidDiagram_true)
        {
            NetworkDiagram test;
            test.ParseLine("  | ");
            test.IsValidDiagram();
            Assert::AreEqual(true, test.IsValidDiagram());
        }

        TEST_METHOD(December19_IsValidDiagram_wrongSymbol)
        {
            NetworkDiagram test;
            test.ParseLine(" - ");
            test.IsValidDiagram();
            Assert::AreEqual(false, test.IsValidDiagram());
        }

        TEST_METHOD(December19_IsValidDiagram_multiplePipes)
        {
            NetworkDiagram test;
            test.ParseLine("|  |");
            test.IsValidDiagram();
            Assert::AreEqual(false, test.IsValidDiagram());
        }

        TEST_METHOD(December19_IsValidDiagram_PipeAndSomethingElse)
        {
            NetworkDiagram test;
            test.ParseLine(" |  +");
            test.IsValidDiagram();
            Assert::AreEqual(false, test.IsValidDiagram());
        }

        TEST_METHOD(December19_GetStartPosition_valid)
        {
            NetworkDiagram test;
            test.ParseLine("     | ");
            Assert::AreEqual(true, Coord::Point(5,0) == test.GetStartPosition());
        }

        TEST_METHOD(December19_GetStartPosition_invalid)
        {
            NetworkDiagram test;
            Assert::AreEqual(true, Coord::Point(-1, -1) == test.GetStartPosition());
        }

        // ---------------------------------------
        // GetNewDirection
        // ---------------------------------------

        /*
        Verify that we stop on space in all directions.

            |   F   -
        */
        TEST_METHOD(December19_GetNewDirection_Stop)
        {
            Matrix::CharMatrix matrix;
            matrix.Set(4, 5, '|');
            matrix.Set(7, 5, 'F');
            matrix.Set(10, 5, '-');

            NetworkDiagram test(matrix);

            // downwards
            Coord::Point dir = Down;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 5), dir));
            Assert::AreEqual(true, Down == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 6), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Down;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 5), dir));
            Assert::AreEqual(true, Down == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 8), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Down;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 5), dir));
            Assert::AreEqual(true, Down == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(11, 5), dir));
            Assert::AreEqual(true, Stop == dir);

            // upwards
            dir = Up;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 5), dir));
            Assert::AreEqual(true, Up == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 4), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Up;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 5), dir));
            Assert::AreEqual(true, Up == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 4), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Up;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 5), dir));
            Assert::AreEqual(true, Up == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 4), dir));
            Assert::AreEqual(true, Stop == dir);

            // leftwards
            dir = Left;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 5), dir));
            Assert::AreEqual(true, Left == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 5), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Left;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 5), dir));
            Assert::AreEqual(true, Left == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(6, 5), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Left;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 5), dir));
            Assert::AreEqual(true, Left == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(9, 5), dir));
            Assert::AreEqual(true, Stop == dir);

            // rightwards
            dir = Right;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 5), dir));
            Assert::AreEqual(true, Right == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(5, 5), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Right;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 5), dir));
            Assert::AreEqual(true, Right == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(8, 5), dir));
            Assert::AreEqual(true, Stop == dir);

            dir = Right;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 5), dir));
            Assert::AreEqual(true, Right == dir);
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(11, 5), dir));
            Assert::AreEqual(true, Stop == dir);
        }

        /*
          |
          A
          -
        */
        TEST_METHOD(December19_GetNewDirection_UpDown_simple)
        {
            Matrix::CharMatrix matrix;
            matrix.Set(1, 1, '|');
            matrix.Set(1, 2, 'A');
            matrix.Set(1, 3, '-');

            NetworkDiagram test(matrix);
            Coord::Point dir = Down;

            // downwards
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 1), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 2), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 3), dir));
            Assert::AreEqual(true, Down == dir);

            // upwards
            dir = Up;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 3), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 2), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 1), dir));
            Assert::AreEqual(true, Up == dir);
        }

        /*
            -F|
        */
        TEST_METHOD(December19_GetNewDirection_LeftRight_simple)
        {
            Matrix::CharMatrix matrix;
            matrix.Set(7, 4, '-');
            matrix.Set(8, 4, 'F');
            matrix.Set(9, 4, '|');

            NetworkDiagram test(matrix);
            Coord::Point dir = Right;

            // rightwards
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 4), dir));
            Assert::AreEqual(true, Right == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(8, 4), dir));
            Assert::AreEqual(true, Right == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(9, 4), dir));
            Assert::AreEqual(true, Right == dir);

            // leftwards
            dir = Left;
            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(9, 4), dir));
            Assert::AreEqual(true, Left == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(8, 4), dir));
            Assert::AreEqual(true, Left == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(7, 4), dir));
            Assert::AreEqual(true, Left == dir);
        }

        /*
           +-+
           | |
           +-+
        */
        TEST_METHOD(December19_GetNewDirection_Corner_plain)
        {
            Matrix::CharMatrix matrix;

            matrix.Set(1, 1, '+');
            matrix.Set(2, 1, '-');
            matrix.Set(3, 1, '+');
            matrix.Set(1, 2, '|');
            matrix.Set(3, 2, '|');
            matrix.Set(1, 3, '+');
            matrix.Set(2, 3, '-');
            matrix.Set(3, 3, '+');

            NetworkDiagram test(matrix);

            // clockwise, starting in top right corner
            Coord::Point dir = Right;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 1), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 3), dir));
            Assert::AreEqual(true, Left == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 3), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 1), dir));
            Assert::AreEqual(true, Right == dir);

            // counter-clockwise, starting in top left corner
            dir = Left;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 1), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(1, 3), dir));
            Assert::AreEqual(true, Right == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 3), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 1), dir));
            Assert::AreEqual(true, Left == dir);
        }

        /*
            +D+
            M H
            +K+
        */
        TEST_METHOD(December19_GetNewDirection_Corner_letters)
        {
            Matrix::CharMatrix matrix;

            matrix.Set(4, 4, '+');
            matrix.Set(5, 4, 'D');
            matrix.Set(6, 4, '+');
            matrix.Set(4, 5, 'M');
            matrix.Set(6, 5, 'H');
            matrix.Set(4, 6, '+');
            matrix.Set(5, 6, 'K');
            matrix.Set(6, 6, '+');

            NetworkDiagram test(matrix);

            // clockwise, starting in top right corner
            Coord::Point dir = Right;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(6, 4), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(6, 6), dir));
            Assert::AreEqual(true, Left == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 6), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 4), dir));
            Assert::AreEqual(true, Right == dir);

            // counter-clockwise, starting in top left corner
            dir = Left;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 4), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(4, 6), dir));
            Assert::AreEqual(true, Right == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(6, 6), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(6, 4), dir));
            Assert::AreEqual(true, Left == dir);
        }

        /*
            +|+
            ---
            +|+
        */
        TEST_METHOD(December19_GetNewDirection_Corner_crossing)
        {
            Matrix::CharMatrix matrix;

            matrix.Set(10, 10, '+');
            matrix.Set(11, 10, '|');
            matrix.Set(12, 10, '+');
            matrix.Set(10, 11, '-');
            matrix.Set(11, 11, '-');
            matrix.Set(12, 11, '-');
            matrix.Set(10, 12, '+');
            matrix.Set(11, 12, '|');
            matrix.Set(12, 12, '+');

            NetworkDiagram test(matrix);

            // clockwise, starting in top right corner
            Coord::Point dir = Right;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(12, 10), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(12, 12), dir));
            Assert::AreEqual(true, Left == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 12), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 10), dir));
            Assert::AreEqual(true, Right == dir);

            // counter-clockwise, starting in top left corner
            dir = Left;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 10), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(10, 12), dir));
            Assert::AreEqual(true, Right == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(12, 12), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(12, 10), dir));
            Assert::AreEqual(true, Left == dir);
        }

        /*
            ++
            ++
        */
        TEST_METHOD(December19_GetNewDirection_Corners_only)
        {
            Matrix::CharMatrix matrix;

            matrix.Set(2, 2, '+');
            matrix.Set(3, 2, '+');
            matrix.Set(2, 3, '+');
            matrix.Set(3, 3, '+');

            NetworkDiagram test(matrix);

            // clockwise, starting in top right corner
            Coord::Point dir = Right;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 2), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 3), dir));
            Assert::AreEqual(true, Left == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(2, 3), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(2, 2), dir));
            Assert::AreEqual(true, Right == dir);

            // counter-clockwise, starting in top left corner
            dir = Left;

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(2, 2), dir));
            Assert::AreEqual(true, Down == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(2, 3), dir));
            Assert::AreEqual(true, Right == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 3), dir));
            Assert::AreEqual(true, Up == dir);

            Assert::AreEqual(true, test.GetNewDirection(Coord::Point(3, 2), dir));
            Assert::AreEqual(true, Left == dir);
        }

        /*
          |
          | +G
          +--+
        */
        TEST_METHOD(December19_GetNewDirection)
        {
            Matrix::CharMatrix matrix;
            // start
            matrix.Set(3, 0, '|');
            // down
            matrix.Set(3, 1, '|');
            // right
            matrix.Set(3, 2, '+');
            matrix.Set(4, 2, '-');
            matrix.Set(5, 2, '-');
            // up
            matrix.Set(6, 2, '+');
            // left
            matrix.Set(6, 1, '+');
            matrix.Set(5, 1, 'G');

            NetworkDiagram test(matrix);
            Coord::Point dir = Down;

            // start -> down
            test.GetNewDirection(Coord::Point(3, 1), dir);
            Assert::AreEqual(true, Down == dir);

            // down -> right
            test.GetNewDirection(Coord::Point(3, 2), dir);
            Assert::AreEqual(true, Right == dir);
            test.GetNewDirection(Coord::Point(5, 2), dir);
            Assert::AreEqual(true, Right == dir);

            // right -> up
            test.GetNewDirection(Coord::Point(6, 2), dir);
            Assert::AreEqual(true, Up == dir);

            // up -> left
            test.GetNewDirection(Coord::Point(6, 1), dir);
            Assert::AreEqual(true, Left == dir);
            test.GetNewDirection(Coord::Point(5, 1), dir);
            Assert::AreEqual(true, Left == dir);

            // left -> stop
            test.GetNewDirection(Coord::Point(4, 1), dir);
            Assert::AreEqual(true, Stop == dir);
        }

        /*
            |
            | +--H-+
            | +G-+ I
            |    | |
            +-F--+ J
        */
        TEST_METHOD(December19_GetPacketPath_noCrossings)
        {
            NetworkDiagram test;
            test.ParseLine("    |");
            test.ParseLine("    | +--H-+");
            test.ParseLine("    | +G-+ I");
            test.ParseLine("    |    | |");
            test.ParseLine("    +-F--+ J");

            Assert::AreEqual(true, test.ProcessDiagram());
            Assert::AreEqual("FGHIJ", test.GetPacketPath().c_str());
        }

        /*
                |
                |  +--+
                A  |  C
            F---|----E|--+
                |  |  |  D
                +B-+  +--+

        Following the path to the end, the letters it sees on its path are ABCDEF.
        */
        TEST_METHOD(December19_AoC_test)
        {
            NetworkDiagram test;
            test.ParseLine("    |         ");
            test.ParseLine("    |  +--+   ");
            test.ParseLine("    A  |  C   ");
            test.ParseLine("F---|----E|--+");
            test.ParseLine("    |  |  |  D");
            test.ParseLine("    +B-+  +--+");

            Assert::AreEqual(true, test.ProcessDiagram());
            Assert::AreEqual("ABCDEF", test.GetPacketPath().c_str());
        }
    };
}
