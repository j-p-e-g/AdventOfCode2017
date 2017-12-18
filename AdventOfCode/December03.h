#pragma once

#include <string>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/3

    Part 1:

    You come across an experimental new kind of memory stored on an infinite two-dimensional grid.

    Each square on the grid is allocated in a spiral pattern starting at a location marked 1 and then counting up while spiraling outward. For example, the first few squares are allocated like this:

        17  16  15  14  13
        18   5   4   3  12
        19   6   1   2  11
        20   7   8   9  10
        21  22  23---> ...

    While this is very space-efficient (no squares are skipped), requested data must be carried back to square 1 (the location of the only access port for this memory system) by programs that can only move up, down, left, or right. They always take the shortest path: the Manhattan Distance between the location of the data and square 1.

    For example:

        Data from square 1 is carried 0 steps, since it's at the access port.
        Data from square 12 is carried 3 steps, such as: down, left, left.
        Data from square 23 is carried only 2 steps: up twice.
        Data from square 1024 must be carried 31 steps.

    How many steps are required to carry the data from the square identified in your puzzle input all the way to the access port?
*/

namespace AdventOfCode {
namespace December03 {

	struct Point
	{
	public:
		Point(int _x, int _y)
			: x(_x)
			, y(_y)
		{
		}

		bool IsValid()
		{
			return x >= 0 && y >= 0;
		}

        bool operator <(const Point& other) const
        {
            return x < other.x || x == other.x && y < other.y;
        }

        bool operator <=(const Point& other) const
        {
            return x < other.x || x == other.x && y <= other.y;
        }

        bool operator >(const Point& other) const
        {
            return !(*this <= other);
        }

        bool operator >=(const Point& other) const
        {
            return (*this == other) || (*this > other);
        }

        bool operator ==(const Point& other) const
		{
			return x == other.x && y == other.y;
		}

        void operator +=(const Point& other)
        {
            x += other.x;
            y += other.y;
        }

		std::wstring ToWString() const
		{
			std::string str = "Point( " + std::to_string(x) + ", " + std::to_string(y) + " )";

			std::wstring wstr;
			wstr.assign(str.begin(), str.end());

			return wstr;
		}

	public:
		int x = 0;
		int y = 0;
	};

	const Point InvalidCoord = Point(-1, -1);

	const Point DirRight = Point(1, 0);
	const Point DirUp = Point(0, -1);
	const Point DirLeft = Point(-1, 0);
	const Point DirDown = Point(0, 1);

	class SpiralMemory
        : protected AdventOfCodeBase
	{
	public:
		SpiralMemory() {};
        SpiralMemory(const std::string& fileName);
        ~SpiralMemory() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
		static Point FindCoord(int id);
		static int GetManhattanDistance(int id);

    protected:
		static bool GetNextDir(Point pos, Point& dir, int& diameter);

    protected:
        int m_number = -1;
	};
}}
