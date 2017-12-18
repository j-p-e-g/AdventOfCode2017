#include "stdafx.h"

#include <iostream>
#include <map>

#include "CodeUtil.h"
#include "December03b.h"

using namespace AdventOfCode::December03;

SumSpiralMemory::SumSpiralMemory(const std::string& fileName)
    : SpiralMemory(fileName)
{
    m_greaterValue = ConstructMapUntilValuePassed(m_number);
}

void SumSpiralMemory::OutputResultToConsole() const
{
    std::cout << "December03.b: result = " << m_greaterValue << std::endl;
}

int SumSpiralMemory::ConstructMapUntilValuePassed(int value)
{
    Point pos = Point(0, 0);
    m_pointMap.emplace(pos, 1);

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

    while (true)
    {
        // continue spiral
        pos += dir;
        if (!GetNextDir(pos, dir, diameter))
        {
            return -1;
        }

        int sum = GetSumOfAdjacentPoints(pos);
        if (sum > value)
        {
            return sum;
        }

        // add new point
        m_pointMap.emplace(pos, sum);
    }
}

int SumSpiralMemory::GetSumOfAdjacentPoints(const Point & p) const
{
    int sum = 0;

    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            Point curr = p;
            curr.x += x;
            curr.y += y;

            const auto& found = m_pointMap.find(curr);
            if (found != m_pointMap.end())
            {
                sum += found->second;
            }
        }

    return sum;
}
