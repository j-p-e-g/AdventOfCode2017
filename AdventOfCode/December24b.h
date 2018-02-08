#pragma once

#include "December24.h"

/*
http://adventofcode.com/2017/day/24

Part 2:

The bridge you've built isn't long enough; you can't jump the rest of the way.

In the example above, there are two longest bridges:

0/2--2/2--2/3--3/4
0/2--2/2--2/3--3/5
Of them, the one which uses the 3/5 component is stronger; its strength is 0+2 + 2+2 + 2+3 + 3+5 = 19.

What is the strength of the longest bridge you can make? If you can make multiple bridges of the longest length, pick the strongest one.
*/

namespace AdventOfCode {
    namespace December24 {

        class PortConnectionB
            : public PortConnection
        {
        public:
            PortConnectionB() {};
            PortConnectionB(const std::string& fileName);
            ~PortConnectionB() = default;

        public:
            // AdventOfCodeBase
            virtual void OutputResultToConsole() const override;
            // ~AdventOfCodeBase

        public:
            void CalculateBestPath(const std::string& start, std::vector<Connection>& bestPath) const override;
        };
    }
}
