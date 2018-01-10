#include "stdafx.h"

#include <iostream>

#include "December22.h"

using namespace AdventOfCode::December22;

InfectedGrid::InfectedGrid()
    : AdventOfCodeBase()
{
    m_matrix.SetDefaultEntry('.');
}

InfectedGrid::InfectedGrid(const std::string& fileName)
    : InfectedGrid()
{
    ReadFile(fileName);
}

bool InfectedGrid::ParseLine(const std::string& inputLine)
{
    int y = m_matrix.GetHeight();
    int x = 0;
    for (const auto& c : inputLine)
    {
        if (!IsValidCell(c))
        {
            return false;
        }

        m_matrix.Set(x++, y, c);
    }

    // update start position
    m_virusPosition = m_matrix.GetMatrixCenter();
    return true;
}

void InfectedGrid::OutputResultToConsole() const
{
    std::cout << "December22.a: result = " << GetNumInfectiousBursts() << std::endl;
}

bool InfectedGrid::IsValidCell(char c)
{
    return (c == '.' || c == '#');
}

int InfectedGrid::GetNumInfectiousBursts() const
{
    return m_infectionCounter;
}

void InfectedGrid::TurnLeft()
{
    UpdateDirection(-1);
}

void InfectedGrid::TurnRight()
{
    UpdateDirection(1);
}

void InfectedGrid::UpdateDirection(int offset)
{
    for (int k = 0; k < m_clockwiseDirections.size(); k++)
    {
        if (m_clockwiseDirections[k] == m_direction)
        {
            int newIndex = static_cast<int>((m_clockwiseDirections.size() + k + offset) % m_clockwiseDirections.size());
            m_direction = m_clockwiseDirections[newIndex];break;
        }
    }
}

void InfectedGrid::MoveForward()
{
    m_virusPosition += m_direction;
}

void InfectedGrid::HandleBursts(int amount)
{
    for (int k = 0; k < amount; k++)
    {
        HandleSingleBurst();
    }
}

void InfectedGrid::HandleSingleBurst()
{
    if (m_matrix.Get(m_virusPosition) == '#')
    {
        // infected
        TurnRight();
        m_matrix.Set(m_virusPosition, '.');
        MoveForward();
    }
    else if (m_matrix.Get(m_virusPosition) == '.')
    {
        // clean
        TurnLeft();
        m_matrix.Set(m_virusPosition, '#');
        IncreaseCounter();
        MoveForward();
    }
}
