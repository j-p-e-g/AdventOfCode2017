#include "stdafx.h"

#include <iostream>

#include "December19.h"

using namespace AdventOfCode::December19;

// -------------------------------------
// Matrix
// -------------------------------------
void Matrix::Set(int x, int y, char value)
{
    if (x < 0 || y < 0)
    {
        return;
    }

    while (y >= m_matrix.size())
    {
        m_matrix.push_back(Row());
    }

    if (x >= m_matrix[y].size())
    {
        for (auto& row : m_matrix)
        {
            while (x >= row.size())
            {
                row.push_back(' ');
            }
        }
    }

    SetValue(x, y, value);
}

void Matrix::SetValue(int x, int y, char value)
{
    m_matrix[y][x] = value;
}

char Matrix::Get(int x, int y) const
{
    if (x < 0 || y < 0 || y >= m_matrix.size() || x >= m_matrix[y].size())
    {
        return ' ';
    }

    return m_matrix[y][x];
}

// -------------------------------------
// NetworkDiagram
// -------------------------------------
NetworkDiagram::NetworkDiagram()
    : AdventOfCodeBase()
{
    m_diagram = std::make_shared<Matrix>();
}

NetworkDiagram::NetworkDiagram(const Matrix& matrix)
{
    m_diagram = std::make_shared<Matrix>(matrix);
}

NetworkDiagram::NetworkDiagram(const std::string& fileName)
    : NetworkDiagram()
{
    ReadFile(fileName);
    ProcessDiagram();
}

bool NetworkDiagram::ParseLine(const std::string& inputLine)
{
    const std::string expectedSymbols = " +-|";
    int y = m_diagram->GetHeight();
    int x = 0;
    for (const auto& c : inputLine)
    {
        // every character must be either an upper-case letter or one of a short list of symbols
        if (expectedSymbols.find(c) == std::string::npos)
        {
            if (!CodeUtils::CodeUtil::CharIsUppercaseLetter(c))
            {
                return false;
            }
        }

        m_diagram->Set(x++, y, c);
    }

    return true;
}

void NetworkDiagram::OutputResultToConsole() const
{
    if (!IsValidDiagram())
    {
        std::cerr << "December19: invalid diagram!" << std::endl;
        return;
    }

    std::cout << "December19.a: result = " << GetPacketPath() << std::endl;
}

bool NetworkDiagram::ProcessDiagram()
{
    m_currentPos = GetStartPosition();
    if (!m_currentPos.IsValid())
    {
        return false;
    }

    m_currentDir = Down;

    // follow the path
    while (true)
    {
        if (!ProcessDiagramStep())
        {
            return false;
        }

        if (Stop == m_currentDir)
        {
            break;
        }
    }

    return true;
}

bool NetworkDiagram::ProcessDiagramStep()
{
    m_currentPos += m_currentDir;
    if (!GetNewDirection(m_currentPos, m_currentDir))
    {
        return false;
    }

    const char symbol = m_diagram->Get(m_currentPos.x, m_currentPos.y);
    if (CodeUtils::CodeUtil::CharIsUppercaseLetter(symbol))
    {
        m_lettersOnPath.push_back(symbol);
    }

    return true;
}

bool NetworkDiagram::GetNewDirection(const CodeUtils::Point& pos, CodeUtils::Point& dir) const
{
    const char symbol = m_diagram->Get(pos.x, pos.y);
    if (symbol == ' ')
    {
        dir = Stop;
        return true;
    }

    // continue until we reach a plus sign
    if (symbol != '+')
    {
        // don't change directions
        return true;
    }

    const std::string validPerpendicularSymbols = "-+|";

    // move into the appropriate perpendicular directions
    if (dir == Down || dir == Up)
    {
        const char leftSymbol = m_diagram->Get(pos.x - 1, pos.y);
        const char rightSymbol = m_diagram->Get(pos.x + 1, pos.y);

        const bool hasLeft = (validPerpendicularSymbols.find(leftSymbol) != std::string::npos)
                              || CodeUtils::CodeUtil::CharIsUppercaseLetter(leftSymbol);
        const bool hasRight = (validPerpendicularSymbols.find(rightSymbol) != std::string::npos)
                               || CodeUtils::CodeUtil::CharIsUppercaseLetter(rightSymbol);

        if (hasLeft && hasRight)
        {
            // unclear, could be either
            return false;
        }

        if (hasLeft)
        {
            dir = Left;
        }
        else if (hasRight)
        {
            dir = Right;
        }
        else
        {
            dir = Stop;
        }

        return true;
    }
    else
    {
        const char upSymbol = m_diagram->Get(pos.x, pos.y - 1);
        const char downSymbol = m_diagram->Get(pos.x, pos.y + 1);

        const bool hasUp = (validPerpendicularSymbols.find(upSymbol) != std::string::npos)
                            || CodeUtils::CodeUtil::CharIsUppercaseLetter(upSymbol);
        const bool hasDown = (validPerpendicularSymbols.find(downSymbol) != std::string::npos)
                            || CodeUtils::CodeUtil::CharIsUppercaseLetter(downSymbol);

        // unclear, could be either
        if (hasUp && hasDown)
        {
            return false;
        }

        if (hasUp)
        {
            dir = Up;
        }
        else if (hasDown)
        {
            dir = Down;
        }
        else
        {
            dir = Stop;
        }

        return true;
    }
}

bool NetworkDiagram::CheckIsValidDirectionSymbol(const char symbol, const CodeUtils::Point& dir) const
{
    switch (symbol)
    {
    case '|':
        return (dir == Left || dir == Right);
    case '-':
        return (dir == Down || dir == Up);
    case ' ':
    case '+':
        return true;
    default:
        if (CodeUtils::CodeUtil::CharIsUppercaseLetter(symbol))
        {
            return true;
        }
    }

    // anything else means the direction is invalid
    return false;
}

bool NetworkDiagram::IsValidDiagram() const
{
    if (m_diagram == nullptr || m_diagram->GetHeight() < 1)
    {
        return false;
    }

    int pipeCount = 0;
    for (int x = 0; x < m_diagram->GetWidth(); x++)
    {
        const char symbol = m_diagram->Get(x, 0);
        switch (symbol)
        {
        case ' ':
            // nothing to do
            break;
        case '|':
            if (++pipeCount > 1)
            {
                // too many pipes
                return false;
            }
            break;
        default:
            // wrong symbol
            return false;
        }
    }

    return true;
}

CodeUtils::Point NetworkDiagram::GetStartPosition() const
{
    CodeUtils::Point pos(-1, -1);

    // Starting at the only line touching the top of the diagram
    if (!IsValidDiagram())
    {
        return pos;
    }

    int startX = -1;
    for (int x = 0; x < m_diagram->GetWidth(); x++)
    {
        if (m_diagram->Get(x, 0) == '|')
        {
            pos = CodeUtils::Point(x, 0);
            break;
        }
    }

    return pos;
}

std::string NetworkDiagram::GetPacketPath() const
{
    return m_lettersOnPath;
}
