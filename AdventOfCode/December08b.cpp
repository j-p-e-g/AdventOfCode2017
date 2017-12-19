#include "stdafx.h"

#include <iostream>

#include "December08b.h"

using namespace AdventOfCode::December08;

RegisterHandlerB::RegisterHandlerB(const std::string& fileName)
{
    ReadFile(fileName);
}

void RegisterHandlerB::OutputResultToConsole() const
{
    std::cout << "December08.b: result = " << GetLargestRegisterValueEver() << std::endl;
}

bool RegisterHandlerB::ApplyCommand(const std::string& commandString)
{
    if (!RegisterHandler::ApplyCommand(commandString))
    {
        return false;
    }

    const RegisterCommand command(commandString);
    const int registerValue = GetValue(command.GetId());
    if (registerValue > m_maxRegisterValue)
    {
        m_maxRegisterValue = registerValue;
    }

    return true;
}

int RegisterHandlerB::GetLargestRegisterValueEver() const
{
    return m_maxRegisterValue;
}
