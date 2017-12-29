#include "stdafx.h"

#include <iostream>

#include "CodeUtil.h"
#include "December17.h"

using namespace AdventOfCode::December17;

CircularVector::CircularVector(const std::vector<int>& initialState, int initialIndex)
    : m_vector(initialState)
    , m_currentIndex(initialIndex)
{
}

bool CircularVector::InsertAfterCurrentIndexWithOffset(int value, int offset)
{
    if (offset < 0)
    {
        return false;
    }

    // update index to point to the inserted value
    if (m_vector.empty())
    {
        m_currentIndex = 0;
    }
    else
    {
        m_currentIndex = (m_currentIndex + offset) % m_vector.size();
        m_currentIndex++;
    }

    if (m_currentIndex == m_vector.size())
    {
        // append at the end
        m_vector.push_back(value);
    }
    else
    {
        // insert
        const auto& found = std::find(m_vector.begin(), m_vector.end(), m_vector[m_currentIndex]);

        m_vector.insert(found, value);
    }

    return true;
}

int CircularVector::GetNextValue() const
{
    if (m_vector.empty())
    {
        return -1;
    }

    const int nextIndex = (m_currentIndex + 1) % m_vector.size();
    return m_vector[nextIndex];
}

void CircularVector::GetVector(std::vector<int>& result)
{
    result = m_vector;
}

// --------------------------------
// Spinlock
// --------------------------------
Spinlock::Spinlock()
{
    // It starts with a circular buffer containing only the value 0, which it marks as the current position.
    const std::vector<int> initialState = { 0 };
    m_circularVector = std::make_shared<CircularVector>(initialState, 0);
}

Spinlock::Spinlock(const std::string& fileName)
    : Spinlock()
{
    ReadFile(fileName);
}

bool Spinlock::ParseLine(const std::string& inputLine)
{
    int number;
    if (!CodeUtils::CodeUtil::ReadStringToInt(inputLine, number, false))
    {
        return false;
    }

    StartSpinlock(number, 2017);
    return true;
}

void Spinlock::OutputResultToConsole() const
{
    std::cout << "December17: result = " << GetNextValue() << std::endl;
}

void Spinlock::StartSpinlock(int stepSize, int repeats)
{
    /*
    It then steps forward through the circular buffer some number of steps (your puzzle input) before inserting the first new value, 1, after the value it stopped on. The inserted value becomes the current position. Then, it steps forward from there the same number of steps, and wherever it stops, inserts after it the second new value, 2, and uses that as the new current position again.
    */
    for (int k = 1; k <= repeats; k++)
    {
        m_circularVector->InsertAfterCurrentIndexWithOffset(k, stepSize);
    }
}

int Spinlock::GetNextValue() const
{
    return m_circularVector->GetNextValue();
}

void Spinlock::GetVector(std::vector<int>& result) const
{
    m_circularVector->GetVector(result);
}
