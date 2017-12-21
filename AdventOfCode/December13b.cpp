#include "stdafx.h"

#include <iostream>
#include <set>

#include "December13b.h"

using namespace AdventOfCode::December13;

FirewallB::FirewallB(const std::string& fileName)
    : Firewall(fileName)
{
}

void FirewallB::OutputResultToConsole() const
{
    std::cout << "December13.b: result = " << GetMinDelayNeededToAvoidDetection() << std::endl;
}

int FirewallB::GetMaxNumberOfGuardCombinations() const
{
    std::set<int> ranges;
    for (const auto& guard : m_guards)
    {
        const int currRange = guard.second->GetRange();
        ranges.emplace(currRange);
    }

    std::set<int> shortList = ranges;

    // if one value is fully divisible by the other, remove the smaller value
    for (const auto& range : ranges)
        for (const auto& range2 : ranges)
        {
            if (range > range2 && range % range2 == 0)
            {
                shortList.erase(range2);
            }
        }

    int product = 1;
    for (const auto& range : shortList)
    {
        // in case of overflow, return the maximum
        if (product * range < product)
        {
            return INT_MAX;
        }

        product *= range;
    }

    return product;
}

int FirewallB::GetMinDelayNeededToAvoidDetection() const
{
    // avoid getting stuck in an infinite loop
    const int maxIterations = GetMaxNumberOfGuardCombinations();

    std::vector<TimeBlock> blockedTimes;
    AddTimesBlockedByGuards(blockedTimes, maxIterations);

    for (int k = 0; k < maxIterations; k++)
    {
        //std::cout << "time " << k << std::endl;

        bool isBlocked = false;
        for (const auto& block : blockedTimes)
        {
            if (block.start == k)
            {
                isBlocked = true;
                break;
            }
            if (block.start > k)
            {
                continue;
            }

            if ((k - block.start) % block.offset == 0)
            {
                isBlocked = true;
                break;
            }
        }

        if (!isBlocked)
        {
            return k;
        }
    }

    return -1;
}

void FirewallB::AddTimesBlockedByGuards(std::vector<TimeBlock>& blockedTimes, int maxTime) const
{
    // for each guard, calculate the first time it blocks slot 0 as well as
    // the time it takes for a full rotation back to slot 0
    for (const auto& guard : m_guards)
    {
        // this is the first time the invader would be caught if starting at time 0
        const int start = guard.second->GetFirstTimeIndexIsReached(0);
        const int fullRotationTime = 2 * (guard.second->GetRange() - 1);
        int nextTime = start;

        // keep adding the time it takes to do a full rotation until the maximum is reached
        while (nextTime <= maxTime)
        {
            // only add if the invader can have reached the guard by that time
            if (nextTime >= guard.first)
            {
                // blocks not the actual time but the one when the invader sets
                // out at position 0
                TimeBlock timeBlock(nextTime - guard.first, fullRotationTime);
                // only add if it doesn't already exist
                if (std::find(blockedTimes.begin(), blockedTimes.end(), timeBlock) == blockedTimes.end())
                {
                    blockedTimes.push_back(timeBlock);
                }
                break;
            }
            nextTime += fullRotationTime;
        }
    }
}
