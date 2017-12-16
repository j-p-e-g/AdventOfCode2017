#include "stdafx.h"
#include "December13.h"

using namespace December13;

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

    /*
    example: 0..2, up
    0: 0
    1: 1
    2: 2, down
    3: 1
    4: 0, up
    5: 1
    6: 2, down

    n: range (0..n)
    k: initial index (0 <= k < n)
    d: dir
    t: time

    if dir == up:
        if t < n-k:
            return k + t
    else:
        if t <= k:
            return k - t
    */
    return curr;
}

void Firewall::AddGuard(int index, std::shared_ptr<Guard> guard)
{
    m_guards.emplace(index, guard);
}

void Firewall::Tick()
{
}

void Firewall::GetIntruderCaughtLocations(int enterTime, std::vector<int>& caughtIndices)
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

int Firewall::GetSecurityScore(int intruderEnterTime, int startingPenalty)
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
