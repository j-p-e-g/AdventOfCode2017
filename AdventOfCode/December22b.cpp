#include "stdafx.h"

#include <iostream>

#include "December22b.h"

using namespace AdventOfCode::December22;

InfectedGridB::InfectedGridB(const std::string& fileName)
    : InfectedGrid()
{
    ReadFile(fileName);
}

void InfectedGridB::OutputResultToConsole() const
{
    std::cout << "December22.b: result = " << GetNumInfectiousBursts() << std::endl;
}

void InfectedGridB::ReverseDirection()
{
    m_direction *= -1;
}

bool InfectedGridB::IsValidCell(char c)
{
    switch (c)
    {
    case '.':
    case '#':
    case 'W':
    case 'F':
        return true;
    default:
        return false;
    }
}

void InfectedGridB::HandleSingleBurst()
{
    char status = m_matrix.Get(GetVirusPosition());
    switch (status)
    {
    case '#': // infected
        TurnRight();
        status = 'F';
        break;
    case 'F': // flagged
        ReverseDirection();
        status = '.';
        break;
    case '.': // clean
        TurnLeft();
        status = 'W';
        break;
    case 'W': // weakened
        // don't change direction
        status = '#';
        IncreaseCounter();
        break;
    default:
        return;
    }

    m_matrix.Set(GetVirusPosition(), status);
    MoveForward();
}
