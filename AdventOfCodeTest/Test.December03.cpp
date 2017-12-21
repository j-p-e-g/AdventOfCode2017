
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December03.h"
#include "../AdventOfCode/CodeUtil.h"

namespace Microsoft
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December03;
    using namespace CodeUtils;

    namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<CodeUtils::Point>(const CodeUtils::Point& t) { return t.ToWString(); }
		}
	}
}

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December03;

    TEST_CLASS(Test_December03)
	{
	public:
        // -------------------------------------
        // ParseLine
        // -------------------------------------
        /*
        empty string
        */
        TEST_METHOD(December03_ParseLine_emptyString)
        {
            SpiralMemory spiral;
            Assert::AreEqual(false, spiral.ParseLine(""));
        }

        /*
        invalid: not a number
        */
        TEST_METHOD(December03_ParseLine_nonNumber)
        {
            SpiralMemory spiral;
            Assert::AreEqual(false, spiral.ParseLine("qtfss"));
        }

        /*
        invalid: contains a second line
        */
        TEST_METHOD(December03_ParseLine_secondLine)
        {
            SpiralMemory spiral;
            Assert::AreEqual(false, spiral.ParseLine("85\n3"));
        }

        //-----------------------------
        // FindCoord
        //-----------------------------
        // test spiral
		/*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_FindCoord_Zero)
		{
			const CodeUtils::Point coord = SpiralMemory::FindCoord(0);
			Assert::AreEqual(CodeUtils::InvalidCoord, coord);
		}

		/*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_FindCoord_NegativeInput)
		{
            const CodeUtils::Point coord = SpiralMemory::FindCoord(-3);
            Assert::AreEqual(CodeUtils::InvalidCoord, coord);
		}

		/*
		starting CodeUtils::Point
		*/
		TEST_METHOD(December03_FindCoord_1)
		{
            const CodeUtils::Point coord = SpiralMemory::FindCoord(1);
            Assert::AreEqual(CodeUtils::Point(0,0), coord);
		}

		/*
		Data from square 12 is carried 3 steps, such as: down, left, left.
		*/
		TEST_METHOD(December03_FindCoord_12)
		{
            const CodeUtils::Point coord = SpiralMemory::FindCoord(12);
            Assert::AreEqual(CodeUtils::Point(2, -1), coord);
		}

		/*
		Data from square 23 is carried only 2 steps: up twice.
		*/
		TEST_METHOD(December03_FindCoord_23)
		{
            const CodeUtils::Point coord = SpiralMemory::FindCoord(23);
			Assert::AreEqual(CodeUtils::Point(0, 2), coord);
		}

        //-----------------------------
		// GetManhattanDistance
        //-----------------------------
        /*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_InvalidInput_Zero)
		{
			Assert::AreEqual(-1, SpiralMemory::GetManhattanDistance(0));
		}

		/*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_InvalidInput_NegativeNumber)
		{
			SpiralMemory test;
			Assert::AreEqual(-1, SpiralMemory::GetManhattanDistance(-14));
		}

		/*
		Data from square 1 is carried 0 steps, since it's at the access port.
		*/
		TEST_METHOD(December03_AoC_Test1)
		{
			SpiralMemory test;
			Assert::AreEqual(0, SpiralMemory::GetManhattanDistance(1));
		}

		/*
		Data from square 12 is carried 3 steps, such as: down, left, left.
		*/
		TEST_METHOD(December03_AoC_Test12)
		{
			SpiralMemory test;
			Assert::AreEqual(3, SpiralMemory::GetManhattanDistance(12));
		}

		/*
		Data from square 23 is carried only 2 steps: up twice.
		*/
		TEST_METHOD(December03_AoC_Test23)
		{
			SpiralMemory test;
			Assert::AreEqual(2, SpiralMemory::GetManhattanDistance(23));
		}

		/*
		Data from square 1024 must be carried 31 steps.
		*/
		TEST_METHOD(December03_AoC_Test1024)
		{
			SpiralMemory test;
			Assert::AreEqual(31, SpiralMemory::GetManhattanDistance(1024));
		}
	};
}

