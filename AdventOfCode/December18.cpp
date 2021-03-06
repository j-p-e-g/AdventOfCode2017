#include "stdafx.h"

#include <iostream>

#include "CodeUtil.h"
#include "December18.h"

using namespace AdventOfCode::December18;

// -------------------------
// CharOrNumber
// -------------------------
CharOrNumber::CharOrNumber(const std::string& str)
{
    if (!CodeUtils::CodeUtil::ReadStringToInt(str, value, true))
    {
        if (str.size() == 1 && str[0] >= 'a' && str[0] <= 'z')
        {
            id = str[0];
            isValid = true;
            isChar = true;
        }
        else
        {
            isValid = false;
        }
    }
    else
    {
        isValid = true;
        isChar = false;
    }
}

// -------------------------
// RegisterCommand(s)
// -------------------------
bool RegisterCommand::Apply(RegisterBase& rd)
{
    rd.SetCurrentIndex(rd.GetCurrentIndex() + 1);
    rd.IncreaseCounter(command);
    return true;
}

bool RegisterSnd::Apply(RegisterBase& rd)
{
    const long long frequency = param.isChar ? rd.GetRegisterValue(param.id) : param.value;
    rd.SetFrequency(frequency);
    RegisterCommand::Apply(rd);

    return true;
}

bool RegisterRcv::Apply(RegisterBase& rd)
{
    const long long value = param.isChar ? rd.GetRegisterValue(param.id) : param.value;
    if (value != 0)
    {
        rd.SetRecoveredFrequency(rd.GetFrequency());
    }

    RegisterCommand::Apply(rd);
    return true;
}

bool RegisterSet::Apply(RegisterBase& rd)
{
    const long long value = param2.isChar ? rd.GetRegisterValue(param2.id) : param2.value;
    rd.SetRegisterValue(param1.id, value);
    RegisterCommand::Apply(rd);

    return true;
}

bool RegisterAdd::Apply(RegisterBase& rd)
{
    const long long prevValue = rd.GetRegisterValue(param1.id);
    const long long bonus = param2.isChar ? rd.GetRegisterValue(param2.id) : param2.value;
    rd.SetRegisterValue(param1.id, prevValue + bonus);
    RegisterCommand::Apply(rd);

    return true;
}

bool RegisterMul::Apply(RegisterBase& rd)
{
    const long long prevValue = rd.GetRegisterValue(param1.id);
    const long long multiplier = param2.isChar ? rd.GetRegisterValue(param2.id) : param2.value;
    rd.SetRegisterValue(param1.id, prevValue * multiplier);
    RegisterCommand::Apply(rd);

    return true;
}

bool RegisterMod::Apply(RegisterBase& rd)
{
    const long long prevValue = rd.GetRegisterValue(param1.id);
    const long long modValue  = param2.isChar ? rd.GetRegisterValue(param2.id) : param2.value;
    
    if (modValue <= 0)
    {
        return false;
    }

    rd.SetRegisterValue(param1.id, prevValue % modValue);
    RegisterCommand::Apply(rd);

    return true;
}

bool RegisterJgz::Apply(RegisterBase& rd)
{
    const long long value = param1.isChar ? rd.GetRegisterValue(param1.id) : param1.value;

    if (value <= 0)
    {
        // skip, increase index normally
        RegisterCommand::Apply(rd);
        return true;
    }

    const int offset = param2.isChar ? static_cast<int>(rd.GetRegisterValue(param2.id)) : param2.value;
    rd.SetCurrentIndex(rd.GetCurrentIndex() + offset);
    rd.IncreaseCounter(command);

    return true;
}

// ----------------------------------
// RegisterDuet
// ----------------------------------
bool RegisterBase::ExecuteNextCommand()
{
    if (m_currentIndex < 0 || m_currentIndex >= m_commands.size())
    {
        return false;
    }

    // may also affect m_currentIndex
    return ApplyCurrentCommand();
}

void RegisterBase::IncreaseCounter(const std::string& key)
{
    auto& found = m_commandCounter.find(key);
    if (found == m_commandCounter.end())
    {
        m_commandCounter.emplace(key, 1);
    }
    else
    {
        found->second++;
    }
}

int RegisterBase::GetCommandCounter(const std::string& key) const
{
    const auto& found = m_commandCounter.find(key);
    if (found == m_commandCounter.end())
    {
        return 0;
    }

    return found->second;
}

bool RegisterBase::ParseLine(const std::string& inputLine)
{
    const std::vector<std::string> elements = CodeUtils::CodeUtil::SplitStringBySpace(inputLine);

    if (elements.size() < 2 || elements.size() > 3)
    {
        return false;
    }

    const std::string command = elements[0];
    const std::string paramStr1 = elements[1];
    const std::string paramStr2 = elements.size() < 3 ? "" : elements[2];

    return ParseCommand(command, CharOrNumber(paramStr1), CharOrNumber(paramStr2));
}

RegisterSolo::RegisterSolo(const std::string& fileName)
    : RegisterBase()
{
    ReadFile(fileName);
    ExecuteCommands();
}

bool RegisterSolo::ParseCommand(const std::string& command, const CharOrNumber& param1, const CharOrNumber& param2)
{
    if (command == "snd")
    {
        if (!param1.isValid || param2.isValid)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterSnd>(param1));
    }
    else if (command == "rcv")
    {
        if (!param1.isValid || param2.isValid)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterRcv>(param1));
    }
    else if (command == "set")
    {
        if (!param1.isValid || !param2.isValid || !param1.isChar)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterSet>(param1, param2));
    }
    else if (command == "add")
    {
        if (!param1.isValid || !param2.isValid || !param1.isChar)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterAdd>(param1, param2));
    }
    else if (command == "mul")
    {
        if (!param1.isValid || !param2.isValid || !param1.isChar)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterMul>(param1, param2));
    }
    else if (command == "mod")
    {
        if (!param1.isValid || !param2.isValid || !param1.isChar || !param2.isChar && param2.value <= 0)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterMod>(param1, param2));
    }
    else if (command == "jgz")
    {
        // jump if greater than zero
        if (!param1.isValid || !param2.isValid || !param1.isChar && param1.value <= 0)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterJgz>(param1, param2));
    }
    else
    {
        return false;
    }

    return true;
}

void RegisterSolo::OutputResultToConsole() const
{
    std::cout << "December18.a: result = " << GetRecoveredFrequency() << std::endl;
}

bool RegisterSolo::ApplyCurrentCommand()
{
    return (m_commands[m_currentIndex]->Apply(*this));
}

bool RegisterSolo::ExecuteCommands()
{
    m_currentIndex = 0;
    while (m_currentIndex >= 0 && m_currentIndex < m_commands.size())
    {
        if (!ExecuteNextCommand())
        {
            return false;
        }

        // abort when we first successfully recover a frequency
        if (m_lastRecoveredFrequency != -1)
        {
            break;
        }
    }

    return true;
}

void RegisterBase::SetRegisterValue(char id, long long value)
{
    auto& found = m_registers.find(id);
    if (found == m_registers.end())
    {
        m_registers.emplace(id, value);
    }
    else
    {
        found->second = value;
    }
}

long long RegisterBase::GetRegisterValue(char id) const
{
    const auto& found = m_registers.find(id);
    if (found == m_registers.end())
    {
        return 0;
    }

    return found->second;
}
