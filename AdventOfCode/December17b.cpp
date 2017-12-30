#include "stdafx.h"

#include <iostream>

#include "CodeUtil.h"
#include "December17b.h"

using namespace AdventOfCode::December17;

SpinlockB::SpinlockB(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool SpinlockB::ParseLine(const std::string& inputLine)
{
    int stepSize;
    if (!CodeUtils::CodeUtil::ReadStringToInt(inputLine, stepSize, false))
    {
        return false;
    }

    /*
    "What is the value after 0 the moment 50000000 is inserted?"

    Zero always stays at index zero (new values are added to the end of the vector instead),
    so we're simply interested in the value at index 1.
    */
    m_lastValueAtIndexOne = CalculateLastValueAtIndexOne(50000000, stepSize);
    return (m_lastValueAtIndexOne >= 0);
}

void SpinlockB::OutputResultToConsole() const
{
    std::cout << "December17.b: result = " << GetLastValueAtIndexOne() << std::endl;
}

int SpinlockB::CalculateLastValueAtIndexOne(long repeats, int stepSize)
{
    // The index a new value is placed can be calculated recursively:
    //   f(k) = (f(k-1) + stepSize) % currentVectorSize + 1
    // The currentVectorSize is always k, so this becomes
    //   f(k) = (f(k-1) + stepSize) % k + 1
    // The recursion starts with f(0) := 0

    // Since we're only interested in index 1, don't bother keeping track of the entire vector.
    // All we need is the current index and the last value that was placed in index 1.
    long currentIndex = 0;
    long lastValueAtIndexOne = -1;

    for (long k = 1; k <= repeats; k++)
    {
        currentIndex = (currentIndex + stepSize) % k + 1;
        if (currentIndex == 1)
        {
            lastValueAtIndexOne = k;
        }
    }

    return lastValueAtIndexOne;
}

int SpinlockB::GetLastValueAtIndexOne() const
{
    return m_lastValueAtIndexOne;
}
