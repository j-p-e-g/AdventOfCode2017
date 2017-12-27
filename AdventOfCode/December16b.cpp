#include "stdafx.h"

#include <iostream>

#include "December16b.h"

using namespace AdventOfCode::December16;

ProgramDancingMasterB::ProgramDancingMasterB(int size, long long numRepeats)
    : ProgramDancingMaster(size)
    , m_numRepetitions(numRepeats)
{
}

ProgramDancingMasterB::ProgramDancingMasterB(const std::string& fileName, int size, long long numRepeats)
    : ProgramDancingMasterB(size, numRepeats)
{
    ReadFile(fileName);
}

bool ProgramDancingMasterB::ParseLine(const std::string& inputLine)
{
    m_formations.emplace(GetFinalFormation(), 0);

    for (int k = 0; k < m_numRepetitions; k++)
    {
        if (!ProgramDancingMaster::ParseLine(inputLine))
        {
            return false;
        }

        const std::string current = GetFinalFormation();
        const auto& found = m_formations.find(current);
        if (found == m_formations.end())
        {
            m_formations.emplace(current, k + 1);
        }
        else
        {
            const int cycleTime = k + 1 - found->second;
            std::cout << "\t" << current << " last seen " << cycleTime << " runs ago (at time " << found->second << ")" << std::endl;

            // run again (with same value that started the first cycle)
            // but only with a limited number of repetitions
            m_numRepetitions = m_numRepetitions % cycleTime;
            m_formations.clear();
            ParseLine(inputLine);
            break;
        }
    }

    return true;
}

void ProgramDancingMasterB::OutputResultToConsole() const
{
    std::cout << "December16.b: result = " << GetFinalFormation() << std::endl;
}
