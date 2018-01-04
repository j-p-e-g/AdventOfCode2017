#pragma once

#include "December19.h"

/*
    https://adventofcode.com/2017/day/19

    Part 2:

    The packet is curious how many steps it needs to go.

    For example, using the same routing diagram from the example above...

            |
            |  +--+
            A  |  C
        F---|--|-E---+
            |  |  |  D
            +B-+  +--+

    ...the packet would go:

        6 steps down (including the first line at the top of the diagram).
        3 steps right.
        4 steps up.
        3 steps right.
        4 steps down.
        3 steps right.
        2 steps up.
        13 steps left (including the F it stops on).

        This would result in a total of 38 steps.

    How many steps does the packet need to go?
*/

namespace AdventOfCode {
namespace December19 {

    class NetworkDiagramB
        : public NetworkDiagram
    {
    public:
        NetworkDiagramB();
        NetworkDiagramB(const std::string& fileName);
        ~NetworkDiagramB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        bool ProcessDiagramStep() override;
        int GetPathLength() const;

    private:
        int m_numSteps = 0;
    };

}}
