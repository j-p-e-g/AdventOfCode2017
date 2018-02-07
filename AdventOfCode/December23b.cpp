#include "stdafx.h"

#include <iostream>

#include "December23b.h"

using namespace AdventOfCode::December23;

/*
* RegisterHandlerB
*/
RegisterHandlerB::RegisterHandlerB(const std::string& fileName)
    : RegisterHandler()
{
    ReadFile(fileName);

    // You flip the switch, which makes register a now start at 1 when the program is executed.
    SetRegisterValue('a', 1);

    ExecuteCommands();
}

void RegisterHandlerB::OutputResultToConsole() const
{
    std::cout << "December23.b: result = " << GetRegisterValue('h') << std::endl;
}

bool SimplifiedRegisterHandlerB::ParseLine(const std::string& inputLine)
{
    return true;
}

void SimplifiedRegisterHandlerB::OutputResultToConsole() const
{
    std::cout << "December23.b: result = " << CountNonPrimes() << std::endl;
}

void SimplifiedRegisterHandlerB::CalculatePrimesUpToValue(const int upperLimit, std::vector<int>& primes) const
{
    // Sieve of Eratosthenes
    std::vector<int> numbers;
    for (int k = 2; k <= upperLimit; k++)
    {
        bool isPrime = true;
        for (const auto p : primes)
        {
            if (k % p == 0)
            {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
        {
            primes.push_back(k);
        }
    }
}

int SimplifiedRegisterHandlerB::CountNonPrimes(int start, int target, int step) const
{
    // sanity check to prevent infinite loops
    if (step == 0 && start != target)
    {
        return -1;
    }

    // pre-compute all prime numbers up to the target value (actually, we only need the values starting at 108100, but that's negligible)
    std::vector<int> primes;
    CalculatePrimesUpToValue(target > start ? target : start, primes);

    int count = 0;
    for (int bValue = start; step > 0 ? bValue <= target : bValue >= target; bValue += step)
    {
        // only increase h if the value isn't prime
        if (std::find(primes.begin(), primes.end(), bValue) == primes.end())
        {
            count++;
        }
    }

    return count;
}
