#include "stdafx.h"

#include <iostream>
#include <math.h>

#include "CodeUtil.h"
#include "CoordPoint.h"
#include "December03.h"

using namespace AdventOfCode::December03;
using namespace Coord;

SpiralMemory::SpiralMemory(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool SpiralMemory::ParseLine(const std::string& inputLine)
{
    return CodeUtils::CodeUtil::ReadStringToInt(inputLine, m_number, false);
}

void SpiralMemory::OutputResultToConsole() const
{
    std::cout << "December03.a: result = " << GetManhattanDistance(m_number) << std::endl;
}

bool SpiralMemory::GetNextDir(Coord::Point pos, Coord::Point& dir, int& diameter)
{
	if (dir == DirRight)
	{
		if (pos.x > diameter)
		{
			diameter++;
			dir = DirUp;
		}
	}
	else if (dir == DirUp)
	{
		if (pos.y == -diameter)
		{
			dir = DirLeft;
		}
	}
	else if (dir == DirLeft)
	{
		if (pos.x == -diameter)
		{
			dir = DirDown;
		}
	}
	else if (dir == DirDown)
	{
		if (pos.y == diameter)
		{
			dir = DirRight;
		}
	}
	else
	{
		return false;
	}

	return true;
}

Point SpiralMemory::FindCoord(int id)
{
	if (id < 1)
	{
		// invalid input
		return InvalidCoord;
	}

	Point pos = Point(0, 0);
	Point dir = DirRight;
	int diameter = 0;

	/*
	spiral movement
	(0,0) -- start point, dir: (1,0)
	(1,0)	-> right, rightmost edge, dir: (0,-1)
	(1,-1)	-> up, upper edge, upper right corner, dir: (-1,0)
	(0,-1)	-> left
	(-1,-1) -> left, leftmost edge, upper left corner, dir: (0,1)
	(-1,0)  -> down
	(-1,1)  -> down, lower edge, lower left corner, dir: (1,0)
	(0,1)	-> right
	(1,1)   -> right, rightmost edge, lower right corner
	*/

	for (int k = 1; k <= id; k++)
	{
		if (k == id)
		{
			break;
		}

		pos += dir;
		if (!GetNextDir(pos, dir, diameter))
		{
			return InvalidCoord;
		}
	}

	return pos;
}

int SpiralMemory::GetManhattanDistance(int id)
{
	Point coord = FindCoord(id);
	if (coord == InvalidCoord)
	{
		return -1;
	}

	return abs(coord.x) + abs(coord.y);
}
