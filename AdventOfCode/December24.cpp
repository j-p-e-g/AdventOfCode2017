#include "stdafx.h"

#include <iostream>
#include <regex>
#include <set>

#include "CodeUtil.h"
#include "December24.h"

using namespace AdventOfCode::December24;

PortConnection::PortConnection(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
    CalculateBestPath("0", m_bestPath);
}

bool PortConnection::ParseLine(const std::string& inputLine)
{
    std::regex regex("(\\d+)\\s*/\\s*");
    std::vector<std::string> elementVector;
    if (!CodeUtils::CodeUtil::SplitStringByRegex(inputLine, elementVector, regex))
    {
        return false;
    }

    if (elementVector.size() != 2)
    {
        return false;
    }

    int valueA, valueB;

    if (!CodeUtils::CodeUtil::ReadStringToInt(elementVector[0], valueA, false)
        || !CodeUtils::CodeUtil::ReadStringToInt(elementVector[1], valueB, false))
    {
        return false;
    }

    AddConnection(elementVector[0], elementVector[1], valueA+valueB);

    return true;
}

void PortConnection::OutputResultToConsole() const
{
    std::cout << "December24: result = " << GetWeight(m_bestPath) << std::endl;
}

void PortConnection::AddConnection(const Connection& connection)
{
    AddNodeAndConnection(connection.valueA, connection);

    if (connection.valueA != connection.valueB)
    {
        AddNodeAndConnection(connection.valueB, connection);
    }
}

void PortConnection::AddConnection(const std::string& start, const std::string& end, int weight)
{
    AddConnection(Connection(start, end, weight));
}

void PortConnection::AddNodeAndConnection(const std::string& node, const Connection& connection)
{
    auto foundNode = m_graph.find(node);
    if (foundNode == m_graph.end())
    {
        m_graph.emplace(node, std::set<Connection>({ connection }));
    }
    else
    {
        foundNode->second.emplace(connection);
    }
}

int PortConnection::GetNumberOfConnections() const
{
    std::set<Connection> connections;

    for (const auto &n : m_graph)
    {
        for (auto& c : n.second)
        {
            connections.emplace(c);
        }
    }

    return static_cast<int>(connections.size());
}

int PortConnection::GetWeight(const std::string& start, const std::string& end) const
{
    const auto& foundStart = m_graph.find(start);
    if (foundStart != m_graph.end())
    {
        for (auto& c : foundStart->second)
        {
            if (c.valueA == start && c.valueB == end
                || c.valueA == end && c.valueB == start)
            {
                return c.strength;
            }
        }
    }

    return -1;
}

void PortConnection::CalculateBestPath(const std::string& start, std::vector<Connection>& bestPath) const
{
    std::set<std::vector<Connection>> allPaths;
    AddPossibleLongestPath(allPaths, start, std::vector<Connection>());

    int bestPathWeight = -1;
    for (const auto& p : allPaths)
    {
        const int weight = GetWeight(p);
        if (weight > bestPathWeight)
        {
            bestPath = p;
            bestPathWeight = weight;
        }
    }
}

void PortConnection::AddPossiblePath(std::set<std::vector<Connection>>& paths, const std::string& currentNode, const std::vector<Connection>& predecessors) const
{
    if (!predecessors.empty())
    {
        paths.emplace(predecessors);
    }

    const auto& found = m_graph.find(currentNode);
    if (found == m_graph.end())
    {
        return;
    }

    for (const auto& c : found->second)
    {
        const auto& foundConnection = std::find(predecessors.begin(), predecessors.end(), c);
        if (foundConnection == predecessors.end())
        {
            std::vector<Connection> pred = predecessors;
            pred.push_back(c);
            AddPossiblePath(paths, c.valueA == currentNode ? c.valueB : c.valueA, pred);
        }
    }
}

void PortConnection::AddPossibleLongestPath(std::set<std::vector<Connection>>& paths, const std::string& currentNode, const std::vector<Connection>& predecessors) const
{
    const auto& found = m_graph.find(currentNode);
    if (found == m_graph.end())
    {
        paths.emplace(predecessors);
        return;
    }

    bool neighbourFound = false;
    for (const auto& c : found->second)
    {
        const auto& foundConnection = std::find(predecessors.begin(), predecessors.end(), c);
        if (foundConnection == predecessors.end())
        {
            std::vector<Connection> pred = predecessors;
            pred.push_back(c);
            AddPossibleLongestPath(paths, c.valueA == currentNode ? c.valueB : c.valueA, pred);
            neighbourFound = true;
        }
    }

    if (!neighbourFound)
    {
        paths.emplace(predecessors);
    }
}

int PortConnection::GetWeight(const std::vector<Connection>& path)
{
    int weight = 0;
    for (const auto& c : path)
    {
        weight += c.strength;
    }
    
    return weight;
}

int PortConnection::CalculateStrongestBridgeWeight()
{
    CalculateBestPath("0", m_bestPath);
    return GetWeight(m_bestPath);
}
