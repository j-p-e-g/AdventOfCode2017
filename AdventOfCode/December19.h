#pragma once

#include <memory>
#include <vector>

#include "AdventOfCodeBase.h"
#include "CodeUtil.h"

/*
    https://adventofcode.com/2017/day/19

    Part 1:

    Somehow, a network packet got lost and ended up here. It's trying to follow a routing diagram (your puzzle input), but it's confused about where to go.

    Its starting point is just off the top of the diagram. Lines (drawn with |, -, and +) show the path it needs to take, starting by going down onto the only line connected to the top of the diagram. It needs to follow this path until it reaches the end (located somewhere within the diagram) and stop there.

    Sometimes, the lines cross over each other; in these cases, it needs to continue going the same direction, and only turn left or right when there's no other option. In addition, someone has left letters on the line; these also don't change its direction, but it can use them to keep track of where it's been. For example:

            |
            |  +--+
            A  |  C
        F---|----E|--+
            |  |  |  D
            +B-+  +--+

    Given this diagram, the packet needs to take the following path:

        Starting at the only line touching the top of the diagram, it must go down, pass through A, and continue onward to the first +.
        Travel right, up, and right, passing through B in the process.
        Continue down (collecting C), right, and up (collecting D).
        Finally, go all the way left through E and stopping at F.

        Following the path to the end, the letters it sees on its path are ABCDEF.

    The little packet looks up at you, hoping you can help it find the way. What letters will it see (in the order it would see them) if it follows the path? (The routing diagram is very wide; make sure you view it without line wrapping.)
*/

namespace AdventOfCode {
namespace December19 {

    typedef std::vector<char> Row;

    class Matrix
    {
    public:
        void Set(int x, int y, char value);
        char Get(int x, int y) const;

        int GetHeight() const { return static_cast<int>(m_matrix.size()); }
        int GetWidth() const { return m_matrix.empty() ? 0 : static_cast<int>(m_matrix[0].size()); }

    private:
        void SetValue(int x, int y, char value);

    private:
        std::vector<Row> m_matrix;
    };

    const CodeUtils::Point Stop(0, 0);
    const CodeUtils::Point Up(0, -1);
    const CodeUtils::Point Down(0, 1);
    const CodeUtils::Point Left(-1, 0);
    const CodeUtils::Point Right(1, 0);

    class NetworkDiagram
        : protected AdventOfCodeBase
    {
    public:
        NetworkDiagram();
        NetworkDiagram(const Matrix& matrix);
        NetworkDiagram(const std::string& fileName);
        ~NetworkDiagram() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        bool ProcessDiagram();
        virtual bool ProcessDiagramStep();
        bool IsValidDiagram() const;
        std::string GetPacketPath() const;
        bool GetNewDirection(const CodeUtils::Point& pos, CodeUtils::Point& dir) const;
        bool CheckIsValidDirectionSymbol(const char symbol, const CodeUtils::Point& dir) const;
        CodeUtils::Point GetStartPosition() const;

    private:
        std::shared_ptr<Matrix> m_diagram;
        CodeUtils::Point m_currentPos;
        CodeUtils::Point m_currentDir;
        std::string m_lettersOnPath;
    };

}
}
