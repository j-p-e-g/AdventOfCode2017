#include "stdafx.h"

#include <iostream>
#include <set>

#include "December14b.h"

using namespace AdventOfCode::December14;

DiskDefragmenterB::DiskDefragmenterB(const std::string& fileName)
    : DiskDefragmenter(fileName)
{
}

void DiskDefragmenterB::OutputResultToConsole() const
{
    std::cout << "December14.b: result = " << GetNumRegions() << std::endl;
}

bool DiskDefragmenterB::FindPointsInRegion(const CodeUtils::Point& p, std::vector<CodeUtils::Point>& connected) const
{
    if (p.x < 0 || p.x >= m_numRows)
    {
        return false;
    }

    if (p.y < 0 || p.y >= m_numColumns)
    {
        return false;
    }

    std::vector<CodeUtils::Point> visited;
    std::vector<CodeUtils::Point> candidates;

    candidates.push_back(p);

    while (!candidates.empty())
    {
        CodeUtils::Point q = candidates[0];
        visited.push_back(q);
        candidates.erase(candidates.begin());

        if (GetBit(q))
        {
            connected.push_back(q);

            bool allowDiagonals = false;
            for (int x = -1; x <= 1; x++)
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0)
                    {
                        continue;
                    }

                    if (!allowDiagonals && x != 0 && y != 0)
                    {
                        continue;
                    }

                    CodeUtils::Point adj = CodeUtils::Point(q.x + x, q.y + y);

                    if (adj.x < 0 || adj.x >= m_numRows || adj.y < 0 || adj.y >= m_numColumns)
                    {
                        continue;
                    }

                    if (std::find(visited.begin(), visited.end(), adj) == visited.end()
                        && std::find(candidates.begin(), candidates.end(), adj) == candidates.end())
                    {
                        candidates.push_back(adj);
                    }
                }
        }
    }

    return true;
}

int DiskDefragmenterB::GetNumRegions() const
{
    std::vector<CodeUtils::Point> candidates;
    for (const auto& point : m_bitMap)
    {
        if (point.second)
        {
            candidates.push_back(point.first);
        }
    }

    std::map<int, CodeUtils::Point> regionCount;

    while (!candidates.empty())
    {
        const CodeUtils::Point curr = candidates[0];

        std::vector<CodeUtils::Point> connected;
        if (FindPointsInRegion(curr, connected))
        {
            regionCount.emplace(static_cast<int>(regionCount.size()), curr);
        }

        for (const auto& con : connected)
        {
            const auto& found = std::find(candidates.begin(), candidates.end(), con);
            if (found != candidates.end())
            {
                candidates.erase(found);
            }
        }
    }

    return static_cast<int>(regionCount.size());
}
