#include "stdafx.h"

#include <iostream>

#include "December19b.h"

using namespace AdventOfCode::December19;

NetworkDiagramB::NetworkDiagramB()
    : NetworkDiagram()
{
}

NetworkDiagramB::NetworkDiagramB(const std::string& fileName)
    : NetworkDiagram()
{
    ReadFile(fileName);
    ProcessDiagram();
}

void NetworkDiagramB::OutputResultToConsole() const
{
    std::cout << "December19.b: result = " << GetPathLength() << std::endl;
}

bool NetworkDiagramB::ProcessDiagramStep()
{
    m_numSteps++;
    return NetworkDiagram::ProcessDiagramStep();
}

int NetworkDiagramB::GetPathLength() const
{
    return m_numSteps;
}
