#include "stdafx.h"
#include "December12.h"

using namespace December12;

ConnectionManager::ConnectionManager(ConnectionMap map)
    : m_connections(map)
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

	return connectedNodes.size();
}

