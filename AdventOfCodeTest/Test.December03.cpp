
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December03.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace December03;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<Point>(const Point& t) { return t.ToWString(); }
		}
	}
}

namespace AdventOfCodeTest
{
	TEST_CLASS(Test_December03)
	{
	public:
		// test spiral
		/*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_FindCoord_Zero)
		{
			SpiralMemory test;
			const Point coord = test.FindCoord(0);
			Assert::AreEqual(InvalidCoord, coord);
		}

		/*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_FindCoord_NegativeInput)
		{
			SpiralMemory test;
			const Point coord = test.FindCoord(-3);
			Assert::AreEqual(InvalidCoord, coord);
		}

		/*
		starting point
		*/
		TEST_METHOD(December03_FindCoord_1)
		{
			SpiralMemory test;
			const Point coord = test.FindCoord(1);
			Assert::AreEqual(Point(0,0), coord);
		}

		/*
		Data from square 12 is carried 3 steps, such as: down, left, left.
		*/
		TEST_METHOD(December03_FindCoord_12)
		{
			SpiralMemory test;
			const Point coord = test.FindCoord(12);
			Assert::AreEqual(Point(2, -1), coord);
		}

		/*
		Data from square 23 is carried only 2 steps: up twice.
		*/
		TEST_METHOD(December03_FindCoord_23)
		{
			SpiralMemory test;
			const Point coord = test.FindCoord(23);
			Assert::AreEqual(Point(0, 2), coord);
		}

		// test Manhattan distance
		/*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_InvalidInput_Zero)
		{
			SpiralMemory test;
			Assert::AreEqual(-1, test.GetManhattanDistance(0));
		}

		/*
		spiral starts counting at 1
		*/
		TEST_METHOD(December03_InvalidInput_NegativeNumber)
		{
			SpiralMemory test;
			Assert::AreEqual(-1, test.GetManhattanDistance(-14));
		}

		/*
		Data from square 1 is carried 0 steps, since it's at the access port.
		*/
		TEST_METHOD(December03_AoC_Test1)
		{
			SpiralMemory test;
			Assert::AreEqual(0, test.GetManhattanDistance(1));
		}

		/*
		Data from square 12 is carried 3 steps, such as: down, left, left.
		*/
		TEST_METHOD(December03_AoC_Test12)
		{
			SpiralMemory test;
			Assert::AreEqual(3, test.GetManhattanDistance(12));
		}

		/*
		Data from square 23 is carried only 2 steps: up twice.
		*/
		TEST_METHOD(December03_AoC_Test23)
		{
			SpiralMemory test;
			Assert::AreEqual(2, test.GetManhattanDistance(23));
		}

		/*
		Data from square 1024 must be carried 31 steps.
		*/
		TEST_METHOD(December03_AoC_Test1024)
		{
			SpiralMemory test;
			Assert::AreEqual(31, test.GetManhattanDistance(1024));
		}
	};
}

