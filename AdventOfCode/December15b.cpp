#include "stdafx.h"

#include <iostream>

#include "December15b.h"

using namespace AdventOfCode::December15;

GeneratorB::GeneratorB(int startValue, int factor, int modValue, int multiple)
    : Generator(startValue, factor, modValue)
    , m_conditionalMultiple(multiple)
{
}

int GeneratorB::CalculateNextNumber()
{
    int number = -1;
    do
    {
        number = Generator::CalculateNextNumber();
    } while (number % m_conditionalMultiple != 0);

    return number;
}

void DuelingGeneratorJudgeB::OutputResultToConsole() const
{
    // After 5 million pairs, but using this new generator logic, what is the judge's final count?
    std::cout << "December15.b: result = " << CountMatchingResults(5000000) << std::endl;
}
