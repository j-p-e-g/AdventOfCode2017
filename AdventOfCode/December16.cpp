#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December16.h"

using namespace AdventOfCode::December16;

ProgramDancingMaster::ProgramDancingMaster(int size)
    : AdventOfCodeBase()
{
    for (int k = 0; k < size; k++)
    {
        m_dancingFormation += ('a' + k);
    }
}

ProgramDancingMaster::ProgramDancingMaster(const std::string& fileName, int size)
    : ProgramDancingMaster(size)
{
    ReadFile(fileName);
}

bool ProgramDancingMaster::ParseLine(const std::string& inputLine)
{
    if (inputLine.empty())
    {
        return true;
    }

    std::vector<std::string> moves;
    std::regex commaRegex("([\\w/]+),\\s*");
    if (!CodeUtils::CodeUtil::SplitStringByRegex(inputLine, moves, commaRegex))
    {
        return false;
    }

    for (const auto& move : moves)
    {
        if (!ApplyDancingMove(move))
        {
            return false;
        }
    }

    return true;
}

void ProgramDancingMaster::OutputResultToConsole() const
{
    std::cout << "December16: result = " << GetFinalFormation() << std::endl;
}

bool ProgramDancingMaster::ApplyDancingMove(const std::string& move)
{
    std::regex spinRegex("s(\\d+)");
    std::regex exchangeRegex("x(\\d+)/(\\d+)");
    std::regex partnerRegex("p(\\w)/(\\w)");
    std::smatch match;

    if (std::regex_match(move, match, spinRegex))
    {
        if (match.size() < 2)
        {
            return false;
        }

        int num = -1;
        if (!CodeUtils::CodeUtil::ReadStringToInt(match[1].str(), num, false))
        {
            return false;
        }

        return ApplySpin(num);
    }

    if (std::regex_match(move, match, exchangeRegex))
    {
        if (match.size() < 3)
        {
            return false;
        }

        int num1 = -1;
        if (!CodeUtils::CodeUtil::ReadStringToInt(match[1].str(), num1, false))
        {
            return false;
        }

        int num2 = -1;
        if (!CodeUtils::CodeUtil::ReadStringToInt(match[2].str(), num2, false))
        {
            return false;
        }

        return ApplySwap(num1, num2);
    }

    if (std::regex_match(move, match, partnerRegex))
    {
        if (match.size() < 3)
        {
            return false;
        }

        return ApplyPartner(match[1].str()[0], match[2].str()[0]);
    }

    return false;
}

bool ProgramDancingMaster::ApplySpin(int length)
{
    if (length <= 0 || length > m_dancingFormation.length())
    {
        return false;
    }

    if (length == m_dancingFormation.length())
    {
        // nothing to do
        return true;
    }

    // makes X programs move from the end to the front, but maintain their order otherwise.
    const int offset = static_cast<int>(m_dancingFormation.length()) - length;

    const std::string suffix = m_dancingFormation.substr(0, offset);
    const std::string prefix = m_dancingFormation.substr(offset); // until the end of the string

    m_dancingFormation = prefix + suffix;

    return true;
}

bool ProgramDancingMaster::ApplyPartner(char char1, char char2)
{
    if (char1 == char2)
    {
        return false;
    }

    if (char1 < 'a' || char1 > 'a' + m_dancingFormation.length())
    {
        return false;
    }

    if (char2 < 'a' || char2 > 'a' + m_dancingFormation.length())
    {
        return false;
    }

    // makes the programs at positions A and B swap places.
    int id1 = -1;
    int id2 = -1;
    for (int k = 0; k < m_dancingFormation.length(); k++)
    {
        if (m_dancingFormation[k] == char1)
        {
            id1 = k;
        }
        else if (m_dancingFormation[k] == char2)
        {
            id2 = k;
        }
    }

    return ApplySwap(id1, id2);
}

bool ProgramDancingMaster::ApplySwap(int id1, int id2)
{
    if (id1 == id2)
    {
        return false;
    }

    if (id1 < 0 || id1 >= m_dancingFormation.length())
    {
        return false;
    }

    if (id2 < 0 || id2 >= m_dancingFormation.length())
    {
        return false;
    }

    // makes the programs at positions A and B swap places.
    int temp = m_dancingFormation[id1];
    m_dancingFormation[id1] = m_dancingFormation[id2];
    m_dancingFormation[id2] = temp;
    return true;
}

std::string ProgramDancingMaster::GetFinalFormation() const
{
    return m_dancingFormation;
}
