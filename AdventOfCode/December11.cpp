#include "stdafx.h"

#include "CodeUtil.h"
#include "December11.h"

#include <iostream>
#include <math.h>
#include <regex>

using namespace AdventOfCode::December11;

InfiniteHexGrid::InfiniteHexGrid()
    : AdventOfCodeBase()
{
    SetupDirections();
}

InfiniteHexGrid::InfiniteHexGrid(const std::string& fileName)
    : InfiniteHexGrid()
{
    ReadFile(fileName);
    m_pathTarget = GetTargetCell();
}

bool InfiniteHexGrid::ParseLine(const std::string& inputLine)
{
    if (inputLine.empty())
    {
        m_path.clear();
        return true;
    }

    std::regex regex("(\\w+),\\s*");
    if (!CodeUtils::CodeUtil::SplitStringByRegex(inputLine, m_path, regex))
    {
        return false;
    }

    for (const auto& step : m_path)
    {
        // invalid direction
        if (m_directions.find(step) == m_directions.end())
        {
            return false;
        }
    }

    return true;
}

void InfiniteHexGrid::OutputResultToConsole() const
{
    std::cout << "December11.a: result = " << GetTargetDistanceToOrigin(m_pathTarget) << std::endl;
}

InfiniteHexGrid::InfiniteHexGrid(const std::vector<std::string>& path)
    : InfiniteHexGrid()
{
    m_path = path;
	m_pathTarget = GetTargetCell();
}

Cell InfiniteHexGrid::GetDirection(std::string dirString) const
{
	const auto found = m_directions.find(dirString);

	if (found == m_directions.end())
	{
		return Cell(0, 0);
	}

	return found->second;
}

void InfiniteHexGrid::SetupDirections()
{
	//      \ n  /              \ (0, -1) /
	//    nw +--+ ne     (-1, 0) +-------+ (1, -1)
	//      /    \              /         \
	//    -+      +-        ---+  (0, 0)   +---
	//      \    /              \         /
	//    sw +--+ se     (-1, 1) +-------+ (1, 0)
	//      / s  \              / (0, 1)  \

	m_directions.emplace("n", Cell(0, -1));
	m_directions.emplace("ne", Cell(1, -1));
	m_directions.emplace("se", Cell(1, 0));
	m_directions.emplace("s", Cell(0, 1));
	m_directions.emplace("sw", Cell(-1, 1));
	m_directions.emplace("nw", Cell(-1, 0));
}

Cell InfiniteHexGrid::GetTargetCell() const
{
	Cell curr = Cell(0, 0);

	for (const auto& dir : m_path)
	{
		curr += GetDirection(dir);
	}

	return curr;
}

std::vector<std::string> InfiniteHexGrid::GetSimplifiedPath() const
{
    int countN = 0;
    int countS = 0;
    int countNE = 0;
    int countNW = 0;
    int countSE = 0;
    int countSW = 0;

    for (const auto& step : m_path)
    {
        if (step == "n")
        {
            countN++;
        }
        else if (step == "ne")
        {
            countNE++;
        }
        else if (step == "nw")
        {
            countNW++;
        }
        else if (step == "s")
        {
            countS++;
        }
        else if (step == "se")
        {
            countSE++;
        }
        else if (step == "sw")
        {
            countSW++;
        }
    }

    // simple cancelation
    if (countN >= countS)
    {
        countN -= countS;
        countS = 0;
    }
    else
    {
        countS -= countN;
        countN = 0;
    }

    if (countNE >= countSW)
    {
        countNE -= countSW;
        countSW = 0;
    }
    else
    {
        countSW -= countNE;
        countNE = 0;
    }

    if (countNW >= countSE)
    {
        countNW -= countSE;
        countSE = 0;
    }
    else
    {
        countSE -= countNW;
        countNW = 0;
    }

    // straighten zigzag paths
    if (countNE > 0 && countNW > 0)
    {
        int numZigZag = std::min(countNE, countNW);
        countN += numZigZag;
        countNE -= numZigZag;
        countNW -= numZigZag;
    }

    if (countSE > 0 && countSW > 0)
    {
        int numZigZag = std::min(countSE, countSW);
        countS += numZigZag;
        countSE -= numZigZag;
        countSW -= numZigZag;
    }

    // construct simplified path (also sorts steps)
    std::vector<std::string> result;

    for (int k = 0; k < countN; k++)
    {
        result.push_back("n");
    }
    for (int k = 0; k < countNE; k++)
    {
        result.push_back("ne");
    }
    for (int k = 0; k < countNW; k++)
    {
        result.push_back("nw");
    }
    for (int k = 0; k < countS; k++)
    {
        result.push_back("s");
    }
    for (int k = 0; k < countSE; k++)
    {
        result.push_back("se");
    }
    for (int k = 0; k < countSW; k++)
    {
        result.push_back("sw");
    }

    return result;
}

int InfiniteHexGrid::GetTargetDistanceToOrigin(const Cell& target)
{
    return std::max({ std::abs(target.x),
                      std::abs(target.y),
                      std::abs(target.x + target.y) });
}

