#include "stdafx.h"

#include <iostream>

#include "December23.h"

using namespace AdventOfCode::December18;
using namespace AdventOfCode::December23;

bool RegisterSub::Apply(RegisterBase& rd)
{
    const long long prevValue = rd.GetRegisterValue(param1.id);
    const long long bonus = param2.isChar ? rd.GetRegisterValue(param2.id) : param2.value;
    rd.SetRegisterValue(param1.id, prevValue - bonus);
    RegisterCommand::Apply(rd);

    return true;
}

bool RegisterJnz::Apply(RegisterBase& rd)
{
    const long long value = param1.isChar ? rd.GetRegisterValue(param1.id) : param1.value;

    if (value == 0)
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

/*
 * RegisterHandler
 */
RegisterHandler::RegisterHandler(const std::string& fileName)
    : RegisterBase()
{
    ReadFile(fileName);
    ExecuteCommands();
}

bool RegisterHandler::ParseCommand(const std::string& command, const CharOrNumber& param1, const CharOrNumber& param2)
{
    if (command == "set")
    {
        if (!param1.isValid || !param2.isValid || !param1.isChar)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterSet>(param1, param2));
    }
    else if (command == "sub")
    {
        if (!param1.isValid || !param2.isValid || !param1.isChar)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterSub>(param1, param2));
    }
    else if (command == "mul")
    {
        if (!param1.isValid || !param2.isValid || !param1.isChar)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterMul>(param1, param2));
    }
    else if (command == "jnz")
    {
        // jump if greater than zero
        if (!param1.isValid || !param2.isValid || !param1.isChar && param1.value <= 0)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterJnz>(param1, param2));
    }
    else
    {
        return false;
    }

    return true;
}

bool RegisterHandler::ApplyCurrentCommand()
{
    return (m_commands[m_currentIndex]->Apply(*this));
}

bool RegisterHandler::ExecuteCommands()
{
    m_currentIndex = 0;
    while (m_currentIndex >= 0 && m_currentIndex < m_commands.size())
    {
        if (!ExecuteNextCommand())
        {
            return false;
        }
    }

    return true;
}

void RegisterHandler::OutputResultToConsole() const
{
    std::cout << "December23: result = " << GetMultiplierCommandCount() << std::endl;
}

int RegisterHandler::GetMultiplierCommandCount() const
{
    return GetCommandCounter("mul");
}
