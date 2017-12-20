#pragma once

#include "December12.h"

/*
    Part 2:

    There are more programs than just the ones in the group containing program ID 0. The rest of them have no way of reaching that group, and still might have no way of reaching each other.

    A group is a collection of programs that can all communicate via pipes either directly or indirectly. The programs you identified just a moment ago are all part of the same group. Now, they would like you to determine the total number of groups.

        In the example above, there were 2 groups: one consisting of programs 0,2,3,4,5,6, and the other consisting solely of program 1.

    How many groups are there in total?
*/

namespace AdventOfCode {
namespace December12 {

    class ConnectionManagerB
        : protected ConnectionManager
    {
    public:
        ConnectionManagerB(const ConnectionMap& map);
        ConnectionManagerB(const std::string& fileName);
        ~ConnectionManagerB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        int GetNumberOfGroups() const;
    };

}}
