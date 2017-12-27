#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December16.h"

using namespace AdventOfCode::December16;

bool DancingMove::IsValid() const
{
    return false;
}

bool DancingMove::ApplyMove(std::string& formation) const
{
    return false;
}

bool Spin::IsValid() const
{
    return m_size > 0;
}

bool Spin::ApplyMove(std::string& formation) const
{
    if (!IsValid())
    {
        return false;
    }

    if (m_size > formation.length())
    {
        return false;
    }

    if (m_size == formation.length())
    {
        // nothing to do
        return true;
    }

    // makes X programs move from the end to the front, but maintain their order otherwise.
    const int offset = static_cast<int>(formation.length()) - m_size;

    const std::string suffix = formation.substr(0, offset);
    const std::string prefix = formation.substr(offset); // until the end of the string

    formation = prefix + suffix;

    return true;
}

bool Exchange::IsValid() const
{
    return m_id1 >= 0 && m_id2 >= 0 && m_id1 != m_id2;
}

bool Exchange::ApplyMove(std::string& formation) const
{
    if (!IsValid())
    {
        return false;
    }

    if (m_id1 >= formation.length())
    {
        return false;
    }

    if (m_id2 >= formation.length())
    {
        return false;
    }

    // makes the programs at positions A and B swap places.
    int temp = formation[m_id1];
    formation[m_id1] = formation[m_id2];
    formation[m_id2] = temp;

    return true;
}

bool Partner::IsValid() const
{
    return m_char1 >= 'a' && m_char1 <= 'z'
        && m_char2 >= 'a' && m_char2 <= 'z'
        && m_char1 != m_char2;
}

bool Partner::ApplyMove(std::string& formation) const
{
    if (!IsValid())
    {
        return false;
    }

    if (m_char1 > 'a' + formation.length())
    {
        return false;
    }

    if (m_char2 > 'a' + formation.length())
    {
        return false;
    }

    // makes the programs at positions A and B swap places.
    int id1 = -1;
    int id2 = -1;
    for (int k = 0; k < formation.length(); k++)
    {
        if (formation[k] == m_char1)
        {
            id1 = k;
        }
        else if (formation[k] == m_char2)
        {
            id2 = k;
        }
    }

    int temp;
    temp = formation[id1];
    formation[id1] = formation[id2];
    formation[id2] = temp;

    return true;
}

// ---------------------------------
// ProgramDancingMaster
// ---------------------------------
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

    for (const auto& moveCommand : moves)
    {
        std::shared_ptr<DancingMove> move;
        if (!ParseDancingMove(moveCommand, move))
        {
            return false;
        }

        if (!ApplyDancingMove(move))
        {
            return false;
        }
    }

    return true;
}

void ProgramDancingMaster::OutputResultToConsole() const
{
    std::cout << "December16.a: result = " << GetFinalFormation() << std::endl;
}

bool ProgramDancingMaster::ParseDancingMove(const std::string& input, std::shared_ptr<DancingMove>& move)
{
    std::regex spinRegex("s(\\d+)");
    std::regex exchangeRegex("x(\\d+)/(\\d+)");
    std::regex partnerRegex("p(\\w)/(\\w)");
    std::smatch match;

    if (std::regex_match(input, match, spinRegex))
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

        move = std::make_shared<Spin>( Spin(num) );
    }
    else if (std::regex_match(input, match, exchangeRegex))
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

        move = std::make_shared<Exchange>( Exchange(num1, num2) );
    }
    else if (std::regex_match(input, match, partnerRegex))
    {
        if (match.size() < 3)
        {
            return false;
        }

        move = std::make_shared<Partner>( Partner(match[1].str()[0], match[2].str()[0]) );
    }
    else
    {
        return false;
    }

    return move->IsValid();
}

bool ProgramDancingMaster::ApplyDancingMove(const std::shared_ptr<DancingMove>& move)
{
    return move->ApplyMove(m_dancingFormation);
}

std::string ProgramDancingMaster::GetFinalFormation() const
{
    return m_dancingFormation;
}
