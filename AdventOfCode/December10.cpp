#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December10.h"

using namespace AdventOfCode::December10;

KnotHash::KnotHash(int hashSize)
    : AdventOfCodeBase()
{
    // create the initial list
    for (int k = 0; k < hashSize; k++)
    {
        m_list.push_back(k);
    }
}

KnotHash::KnotHash(const std::string& fileName, int hashSize)
    : KnotHash(hashSize)
{
    ReadFile(fileName);
}

bool KnotHash::ParseLine(const std::string& inputLine)
{
    std::regex regex("(\\w+)\\s*,\\s*");
    std::vector<std::string> suffixVector;
    if (!CodeUtils::CodeUtil::SplitStringByRegex(inputLine, suffixVector, regex))
    {
        return false;
    }

    std::vector<int> input;
    for (const auto& elem : suffixVector)
    {
        int number = 0;
        if (!CodeUtils::CodeUtil::ReadStringToInt(elem, number, false))
        {
            return false;
        }

        // Lengths larger than the size of the list are invalid.
        if (number < 0 || number > static_cast<int>(m_list.size()))
        {
            return false;
        }

        input.push_back(number);
    }

    ApplyInput(input);
    return true;
}

void KnotHash::OutputResultToConsole() const
{
    std::cout << "December10: result = " << GetCheckSum() << std::endl;
}

void KnotHash::ApplyInput(const std::vector<int>& input)
{
    int id = 0;
    int skipSize = 0;
    for (const auto& len : input)
    {
        InvertSubList(m_list, id, len);
        // Move the current position forward by that length plus the skip size
        id = (id + len + skipSize) % m_list.size();
        // Increase the skip size by one.
        skipSize++;
    }
}

bool KnotHash::InvertSubList(std::vector<int>& list, int id, int length)
{
    if (id < 0 || length < 0)
    {
        return false;
    }

    for (int k = 0; k < std::floor(length / 2); k++)
    {
        int id1 = (id + k) % list.size();
        int id2 = (id + length - k - 1) % list.size();

        // swap values
        int temp = list[id1];
        list[id1] = list[id2];
        list[id2] = temp;
    }

    return true;
}

int KnotHash::GetCheckSum() const
{
    if (m_list.size() < 2)
    {
        return -1;
    }

	return m_list[0] * m_list[1];
}
