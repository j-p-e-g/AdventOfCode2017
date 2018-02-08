#include "stdafx.h"

#include <iostream>
#include <regex>
#include <set>

#include "CodeUtil.h"
#include "December24b.h"

using namespace AdventOfCode::December24;

PortConnectionB::PortConnectionB(const std::string& fileName)
    : PortConnection()
{
    ReadFile(fileName);
    CalculateBestPath("0", m_bestPath);
}

void PortConnectionB::OutputResultToConsole() const
{
    std::cout << "December24.b: result = " << GetWeight(m_bestPath) << std::endl;
}

void PortConnectionB::CalculateBestPath(const std::string& start, std::vector<Connection>& bestPath) const
{
    std::set<std::vector<Connection>> allPaths;
    AddPossibleLongPath(allPaths, start, std::vector<Connection>());

    std::cout << "      #paths: " << allPaths.size() << std::endl;

    int longestPath = 0;
    int bestPathWeight = -1;
    for (const auto& p : allPaths)
    {
        const int weight = GetWeight(p);

        if (p.size() > longestPath
            || p.size() == longestPath && weight > bestPathWeight)
        {
            longestPath = static_cast<int>(p.size());
            bestPathWeight = weight;
            bestPath = p;
        }
    }
}
