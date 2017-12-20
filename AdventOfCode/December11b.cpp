#include "stdafx.h"

#include <iostream>

#include "December11b.h"

using namespace AdventOfCode::December11;

InfiniteHexGridB::InfiniteHexGridB(const std::vector<std::string>& path)
    : InfiniteHexGrid(path)
{
}

InfiniteHexGridB::InfiniteHexGridB(const std::string& fileName)
    : InfiniteHexGrid(fileName)
{
}

void InfiniteHexGridB::OutputResultToConsole() const
{
    std::cout << "December11.b: result = " << GetMaxDistanceFromOriginEver() << std::endl;
}

int InfiniteHexGridB::GetMaxDistanceFromOriginEver() const
{
    int maxDistance = 0;

    Cell curr = Cell(0, 0);
    for (const auto& step : m_path)
    {
        curr += GetDirection(step);
        int distance = GetTargetDistanceToOrigin(curr);
        if (distance > maxDistance)
        {
            maxDistance = distance;
        }
    }

    return maxDistance;
}
