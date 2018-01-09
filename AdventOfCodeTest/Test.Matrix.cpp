
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/Matrix.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace Matrix;

    TEST_CLASS(Test_Matrix)
    {
    public:
        // -------------------------------------
        // character matrix
        // -------------------------------------
        TEST_METHOD(CharMatrix_Get_invalid)
        {
            CharMatrix matrix;
            Assert::AreEqual(' ', matrix.Get(-3, -6));
        }

        TEST_METHOD(CharMatrix_Get_empty)
        {
            CharMatrix matrix;
            Assert::AreEqual(' ', matrix.Get(15, 37));
        }

        TEST_METHOD(CharMatrix_Set_empty)
        {
            CharMatrix matrix;
            matrix.Set(3, 5, 'a');

            Assert::AreEqual('a', matrix.Get(3, 5));
            // everything else is treated as space
            Assert::AreEqual(' ', matrix.Get(2, 1));
            Assert::AreEqual(' ', matrix.Get(7, 9));
            Assert::AreEqual(6, matrix.GetHeight());
            Assert::AreEqual(4, matrix.GetWidth());
        }

        TEST_METHOD(CharMatrix_Set_overwrite)
        {
            CharMatrix matrix;
            matrix.Set(4, 1, 'x');

            Assert::AreEqual('x', matrix.Get(4, 1));
            Assert::AreEqual(2, matrix.GetHeight());
            Assert::AreEqual(5, matrix.GetWidth());

            matrix.Set(4, 1, 'z');
            Assert::AreEqual('z', matrix.Get(4, 1));
        }

        TEST_METHOD(CharMatrix_Equals)
        {
            CharMatrix matrix;
            matrix.Set(0, 1, 'a');
            matrix.Set(1, 1, 'b');

            CharMatrix matrix2;
            matrix2.Set(1, 1, 'b');
            matrix2.Set(0, 1, 'a');

            Assert::AreEqual(true, matrix.Equals(matrix2));
            Assert::AreEqual(true, matrix2.Equals(matrix));
        }

        TEST_METHOD(CharMatrix_NotEquals)
        {
            CharMatrix matrix;
            matrix.Set(0, 1, 'a');
            matrix.Set(1, 1, 'b');

            CharMatrix matrix2;
            matrix2.Set(0, 1, 'a');
            matrix2.Set(1, 0, 'b');

            Assert::AreEqual(false, matrix.Equals(matrix2));
            Assert::AreEqual(false, matrix2.Equals(matrix));
        }

        TEST_METHOD(CharMatrix_CountValue)
        {
            CharMatrix matrix;
            matrix.Set(3, 2, 'q');
            matrix.Set(3, 3, 'q');
            matrix.Set(1, 0, 'r');

            Assert::AreEqual(2, matrix.CountValue('q'));
            Assert::AreEqual(1, matrix.CountValue('r'));
            // remaining 16-3 elements are spaces
            Assert::AreEqual(13, matrix.CountValue(' '));
        }

        TEST_METHOD(CharMatrix_DoHorizontalMirrorFlip_2x2)
        {
            CharMatrix matrix;
            matrix.Set(0, 0, 'a');
            matrix.Set(1, 0, 'b');
            matrix.Set(0, 1, 'c');
            matrix.Set(1, 1, 'd');

            matrix.DoHorizontalMirrorFlip();

            // ab -> ba
            // cd    dc
            Assert::AreEqual('b', matrix.Get(0, 0));
            Assert::AreEqual('a', matrix.Get(1, 0));
            Assert::AreEqual('d', matrix.Get(0, 1));
            Assert::AreEqual('c', matrix.Get(1, 1));
        }

        TEST_METHOD(CharMatrix_DoHorizontalMirrorFlip_3x3)
        {
            CharMatrix matrix;
            matrix.Set(0, 0, 'r');
            matrix.Set(1, 0, 's');
            matrix.Set(2, 0, 't');
            matrix.Set(0, 1, 'u');
            matrix.Set(1, 1, 'v');
            matrix.Set(2, 1, 'w');
            matrix.Set(0, 2, 'x');
            matrix.Set(1, 2, 'y');
            matrix.Set(2, 2, 'z');

            matrix.DoHorizontalMirrorFlip();

            // rst    tsr
            // uvw -> wvu
            // xyz    zyx
            Assert::AreEqual('t', matrix.Get(0, 0));
            Assert::AreEqual('s', matrix.Get(1, 0));
            Assert::AreEqual('r', matrix.Get(2, 0));
            Assert::AreEqual('w', matrix.Get(0, 1));
            Assert::AreEqual('v', matrix.Get(1, 1));
            Assert::AreEqual('u', matrix.Get(2, 1));
            Assert::AreEqual('z', matrix.Get(0, 2));
            Assert::AreEqual('y', matrix.Get(1, 2));
            Assert::AreEqual('x', matrix.Get(2, 2));
        }

        TEST_METHOD(CharMatrix_DoVerticalMirrorFlip_2x2)
        {
            CharMatrix matrix;
            matrix.Set(0, 0, 'a');
            matrix.Set(1, 0, 'b');
            matrix.Set(0, 1, 'c');
            matrix.Set(1, 1, 'd');

            matrix.DoVerticalMirrorFlip();

            // ab -> cd
            // cd    ab
            Assert::AreEqual('c', matrix.Get(0, 0));
            Assert::AreEqual('d', matrix.Get(1, 0));
            Assert::AreEqual('a', matrix.Get(0, 1));
            Assert::AreEqual('b', matrix.Get(1, 1));
        }

        TEST_METHOD(CharMatrix_DoVerticalMirrorFlip_3x3)
        {
            CharMatrix matrix;
            matrix.Set(0, 0, 'r');
            matrix.Set(1, 0, 's');
            matrix.Set(2, 0, 't');
            matrix.Set(0, 1, 'u');
            matrix.Set(1, 1, 'v');
            matrix.Set(2, 1, 'w');
            matrix.Set(0, 2, 'x');
            matrix.Set(1, 2, 'y');
            matrix.Set(2, 2, 'z');

            matrix.DoVerticalMirrorFlip();

            // rst    xyz
            // uvw -> uvw
            // xyz    rst
            Assert::AreEqual('x', matrix.Get(0, 0));
            Assert::AreEqual('y', matrix.Get(1, 0));
            Assert::AreEqual('z', matrix.Get(2, 0));
            Assert::AreEqual('u', matrix.Get(0, 1));
            Assert::AreEqual('v', matrix.Get(1, 1));
            Assert::AreEqual('w', matrix.Get(2, 1));
            Assert::AreEqual('r', matrix.Get(0, 2));
            Assert::AreEqual('s', matrix.Get(1, 2));
            Assert::AreEqual('t', matrix.Get(2, 2));
        }

        TEST_METHOD(CharMatrix_SwapXAndY_invalid)
        {
            CharMatrix matrix;
            matrix.Set(0, 0, 'a');
            matrix.Set(1, 0, 'b');
            matrix.Set(2, 0, 'c');
            matrix.Set(0, 1, 'd');
            matrix.Set(1, 1, 'e');
            matrix.Set(2, 1, 'e');

            // fails for non-square matrices
            Assert::AreEqual(false, matrix.SwapXAndY());
        }

        TEST_METHOD(CharMatrix_SwapXAndY_2x2)
        {
            CharMatrix matrix;
            matrix.Set(0, 0, 'a');
            matrix.Set(1, 0, 'b');
            matrix.Set(0, 1, 'c');
            matrix.Set(1, 1, 'd');

            Assert::AreEqual(true, matrix.SwapXAndY());

            // ab -> ac
            // cd    bd
            Assert::AreEqual('a', matrix.Get(0, 0));
            Assert::AreEqual('c', matrix.Get(1, 0));
            Assert::AreEqual('b', matrix.Get(0, 1));
            Assert::AreEqual('d', matrix.Get(1, 1));
        }

        TEST_METHOD(CharMatrix_SwapXAndY_3x3)
        {
            CharMatrix matrix;
            matrix.Set(0, 0, 'r');
            matrix.Set(1, 0, 's');
            matrix.Set(2, 0, 't');
            matrix.Set(0, 1, 'u');
            matrix.Set(1, 1, 'v');
            matrix.Set(2, 1, 'w');
            matrix.Set(0, 2, 'x');
            matrix.Set(1, 2, 'y');
            matrix.Set(2, 2, 'z');

            Assert::AreEqual(true, matrix.SwapXAndY());

            // rst    rux
            // uvw -> svy
            // xyz    twz
            Assert::AreEqual('r', matrix.Get(0, 0));
            Assert::AreEqual('u', matrix.Get(1, 0));
            Assert::AreEqual('x', matrix.Get(2, 0));
            Assert::AreEqual('s', matrix.Get(0, 1));
            Assert::AreEqual('v', matrix.Get(1, 1));
            Assert::AreEqual('y', matrix.Get(2, 1));
            Assert::AreEqual('t', matrix.Get(0, 2));
            Assert::AreEqual('w', matrix.Get(1, 2));
            Assert::AreEqual('z', matrix.Get(2, 2));
        }
    };
}
