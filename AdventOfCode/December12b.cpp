#include "stdafx.h"

#include <iostream>

#include "December12b.h"

using namespace AdventOfCode::December12;

ConnectionManagerB::ConnectionManagerB(const ConnectionMap& map)
    : ConnectionManager(map)
{
}

ConnectionManagerB::ConnectionManagerB(const std::string& fileName)
    : ConnectionManager(fileName)
{
}

void ConnectionManagerB::OutputResultToConsole() const
{
    std::cout << "December12.b: result = " << GetNumberOfGroups() << std::endl;
}

int ConnectionManagerB::GetNumberOfGroups() const
{
    int groupCount = 0;
    std::set<int> checkedNodes;
    for (const auto& connection : m_connections)
    {
        if (std::find(checkedNodes.begin(), checkedNodes.end(), connection.first) == checkedNodes.end())
        {
            groupCount++;
            for (const auto& elem : connection.second)
            {
                checkedNodes.emplace(elem);
            }
        }
    }

    return groupCount;
}
