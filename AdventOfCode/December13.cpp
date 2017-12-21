#include "stdafx.h"

#include <iostream>
#include <regex>

#include "December13.h"

using namespace AdventOfCode::December13;

// ---------------------------
// Guard
// ---------------------------
Guard::Guard(int range, int startIndex, Direction dir)
    : m_range(range)
    , m_startingIndex(startIndex)
    , m_startingDir(dir)
{
    // switch directions if already at the turning point
    if (m_startingDir == DIR_Down && m_startingIndex == 0)
    {
        m_startingDir = DIR_Up;
    }
    else if (m_startingDir == DIR_Up && m_startingIndex == m_range - 1)
    {
        m_startingDir = DIR_Down;
    }
}

bool Guard::IsValid() const
{
    return m_startingIndex >= 0 && m_startingIndex < m_range;
}

int Guard::GetIndexAtTime(int t) const
{
    if (!IsValid() || t < 0)
    {
        return -1;
    }

    int curr = m_startingIndex;
    Direction dir = m_startingDir;

    for (int counter = 0; counter < t; counter++)
    {
        switch (dir)
        {
        case DIR_Up:
            if (++curr == m_range - 1)
            {
                dir = DIR_Down;
            }
            break;
        case DIR_Down:
            if (--curr == 0)
            {
                dir = DIR_Up;
            }
            break;
        }
    }

    return curr;
}

int Guard::GetFirstTimeIndexIsReached(int index) const
{
    if (m_startingIndex == index)
    {
        return 0;
    }

    if (m_startingDir == DIR_Down)
    {
        if (index < m_startingIndex)
        {
            return m_startingIndex - index;
        }
        else
        {
            return m_startingIndex + index;
        }
    }

    if (m_startingDir == DIR_Up)
    {
        if (index > m_startingIndex)
        {
            return index - m_startingIndex;
        }
        else
        {
            return 2 * (m_range - 1) - m_startingIndex - index;
        }
    }

    return -1;
}

// ----------------------------
// Firewall
// ----------------------------

Firewall::Firewall(const std::string& fileName)
{
    ReadFile(fileName);
}

bool Firewall::ParseLine(const std::string& inputLine)
{
    std::regex regex("\\s*(\\d+)\\s*:\\s*(\\d+)\\s*");
    std::smatch match;
    if (!std::regex_match(inputLine, match, regex))
    {
        return false;
    }

    if (match.size() < 3)
    {
        return false;
    }

    if (!match[1].matched || !match[2].matched)
    {
        return false;
    }

    int id = atoi(match[1].str().c_str());
    int range = atoi(match[2].str().c_str());

    std::shared_ptr<Guard> guard = std::make_shared<Guard>(range, 0);
    if (!guard->IsValid())
    {
        return false;
    }

    AddGuard(id, guard);
    return true;
}

void Firewall::OutputResultToConsole() const
{
    std::cout << "December13.a: result = " << GetSecurityScore(0, 0) << std::endl;
}

void Firewall::AddGuard(int index, std::shared_ptr<Guard> guard)
{
    m_guards.emplace(index, guard);
}

void Firewall::GetIntruderCaughtLocations(int enterTime, std::vector<int>& caughtIndices) const
{
    caughtIndices.clear();

    for (const auto& guard : m_guards)
    {
        const int guardIndex = guard.first;
        const int guardSlotWhenVisited = guard.second->GetIndexAtTime(enterTime + guardIndex);

        // intruder moves along at slot 0
        if (0 == guardSlotWhenVisited)
        {
            caughtIndices.push_back(guardIndex);
        }
    }
}

int Firewall::GetSecurityScore(int intruderEnterTime, int startingPenalty) const
{
    std::vector<int> caughtIndices;
    GetIntruderCaughtLocations(intruderEnterTime, caughtIndices);

    int score = 0;
    for (const auto& index : caughtIndices)
    {
        const auto& foundGuard = m_guards.find(index);
        if (foundGuard != m_guards.end())
        {
            score += (index + startingPenalty) * foundGuard->second->GetRange();
        }
    }

    return score;
}
