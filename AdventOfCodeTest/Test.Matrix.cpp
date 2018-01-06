
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
            // everything else is auto-entered as space
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
    };
}
