#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December12.h"

using namespace AdventOfCode::December12;

ConnectionManager::ConnectionManager(const std::string& fileName)
{
    ReadFile(fileName);
    ProcessConnections();
}

bool ConnectionManager::ParseLine(const std::string& inputLine)
{
    // input format: \d+ <-> [\d+,]*\d+
    std::regex regex("\\s*(\\d+)\\s*<->\\s*([\\d,\\s]+)");
    std::smatch match;

    if (!std::regex_match(inputLine, match, regex))
    {
        return false;
    }

    Connection connection;

    // 0: entire line
    // 1: first number
    // 2: suffix (list of comma-separated numbers)
    for (int index = 0; index < match.size(); index++)
    {
        const auto m = match[index];
        switch (index)
        {
        case 1:
            if (!m.matched)
            {
                return false;
            }
            connection.first = atoi(m.str().c_str());
            break;
        case 2:
        {
            if (!m.matched)
            {
                return false;
            }

            std::regex regex("(\\w+)\\s*,\\s*");
            std::vector<std::string> suffixVector;
            CodeUtils::CodeUtil::SplitStringByRegex(m.str(), suffixVector, regex);

            for (const auto& elem : suffixVector)
            {
                int number = 0;
                if (!CodeUtils::CodeUtil::ReadStringToInt(elem, number, false))
                {
                    return false;
                }

                connection.second.emplace(number);
            }

            if (suffixVector.size() != connection.second.size())
            {
                // contains duplicates
                return false;
            }
        }
        }
    }

    AddConnection(connection);
    return true;
}

void ConnectionManager::AddConnection(Connection connection)
{
    m_connections.emplace(connection.first, connection.second);
}

void ConnectionManager::OutputResultToConsole() const
{
    std::cout << "December12: result = " << GetGroupSize(0) << std::endl;
}

ConnectionManager::ConnectionManager(ConnectionMap map)
    : m_connections(map)
{
    ProcessConnections();
}

void ConnectionManager::ProcessConnections()
{
    bool loop = true;

    while (loop)
    {
        loop = false;
        for (auto& connection : m_connections)
        {
            const int key = connection.first;

            // add self to set
            connection.second.emplace(key);

            for (const auto& value : connection.second)
            {
                // ensure that every element in the list references all other elements
                auto& foundInMap = m_connections.find(value);
                if (foundInMap == m_connections.end())
                {
                    // copy entire list to new map entry
                    m_connections.emplace(value, connection.second);
                    loop = true;
                }
                else
                {
                    for (const auto& val2 : connection.second)
                    {
                        const auto& foundInSet = foundInMap->second.find(val2);
                        if (foundInSet == foundInMap->second.end())
                        {
                            foundInMap->second.emplace(val2);
                            loop = true;
                        }
                    }
                }
            }
        }
    }
}

void ConnectionManager::GetConnectedNodes(int id, std::set<int>& connectedNodes) const
{
    const auto& found = m_connections.find(id);
    if (found != m_connections.end())
    {
        connectedNodes = found->second;
    }
}

int ConnectionManager::GetGroupSize(int id) const
{
    std::set<int> connectedNodes;
    GetConnectedNodes(id, connectedNodes);

	return static_cast<int>(connectedNodes.size());
}

