#include "stdafx.h"

#include <iostream>

#include "December15.h"

using namespace AdventOfCode::December15;

Generator::Generator(int startValue, int factor, int modValue)
    : m_currentValue(startValue)
    , m_factor(factor)
    , m_modValue(modValue)
{
}

int Generator::CalculateNextNumber()
{
    /*
    To create its next value, a generator will take the previous value it produced, multiply it by a factor (generator A uses 16807; generator B uses 48271), and then keep the remainder of dividing that resulting product by 2147483647. That final remainder is the value it produces next.
    */

    const long long product = (long long) m_currentValue * m_factor;
    m_currentValue = product % m_modValue;

    return m_currentValue;
}

// -------------------------------------
// 
// -------------------------------------
bool DuelingGeneratorJudge::ParseLine(const std::string& inputLine)
{
    return true;
}

void DuelingGeneratorJudge::OutputResultToConsole() const
{
    // After 40 million pairs, what is the judge's final count?
    std::cout << "December15.a: result = " << CountMatchingResults(40000000) << std::endl;
}

void DuelingGeneratorJudge::AddGenerator(std::shared_ptr<Generator> generator)
{
    m_duelingGenerators.push_back(generator);
}

bool DuelingGeneratorJudge::CompareGeneratorOutcomes() const
{
    // we're only comparing the "lowest 16 bits of both values"
    // ... which we can get by running a modulo against (16-bit + 1)
    // 16 bit is max. 65535 -> so do % 65536
    const long long MOD_COMPARE_VALUE = 65536;

    long long prevValue = -1;

    for (auto& gen : m_duelingGenerators)
    {
        long long value = gen->CalculateNextNumber() % MOD_COMPARE_VALUE;
        if (prevValue == -1)
        {
            prevValue = value;
        }
        else if (prevValue != value)
        {
            return false;
        }
    }
    
    return true;
}

int DuelingGeneratorJudge::CountMatchingResults(long long amount) const
{
    int matchCount = 0;

    for (int k = 0; k < amount; k++)
    {
        if (CompareGeneratorOutcomes())
        {
            matchCount++;
        }
    }

    return matchCount;
}
