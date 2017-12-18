#pragma once

#include <map>
#include <set>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/12

    Part 1:

    Each program has one or more programs with which it can communicate, and these pipes are bidirectional; if 8 says it can communicate with 11, then 11 will say it can communicate with 8.

    You need to figure out how many programs are in the group that contains program ID 0.

    For example, suppose you go door-to-door like a travelling salesman and record the following list:

        0 <-> 2
        1 <-> 1
        2 <-> 0, 3, 4
        3 <-> 2, 4
        4 <-> 2, 3, 6
        5 <-> 6
        6 <-> 4, 5

    In this example, the following programs are in the group that contains program ID 0:

    Program 0 by definition.
    Program 2, directly connected to program 0.
    Program 3 via program 2.
    Program 4 via program 2.
    Program 5 via programs 6, then 4, then 2.
    Program 6 via programs 4, then 2.

    Therefore, a total of 6 programs are in this group; all but program 1, which has a pipe that connects it to itself.

    How many programs are in the group that contains program ID 0?
*/
/*
    Part 2:

    There are more programs than just the ones in the group containing program ID 0. The rest of them have no way of reaching that group, and still might have no way of reaching each other.

    A group is a collection of programs that can all communicate via pipes either directly or indirectly. The programs you identified just a moment ago are all part of the same group. Now, they would like you to determine the total number of groups.

        In the example above, there were 2 groups: one consisting of programs 0,2,3,4,5,6, and the other consisting solely of program 1.

    How many groups are there in total?
*/

namespace AdventOfCode {
namespace December12 {

    typedef std::pair<int, std::set<int>> Connection;
    typedef std::map<int, std::set<int>> ConnectionMap;

	class ConnectionManager
        : protected AdventOfCodeBase
	{
	public:
        ConnectionManager() {};
        ConnectionManager(ConnectionMap map);
        ConnectionManager(const std::string& fileName);
        ~ConnectionManager() = default;

    public:
        // AdventOfCodeBase
        bool ParseLine(const std::string& inputLine) override;
        void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        void AddConnection(Connection connection);
        void GetConnectedNodes(int id, std::set<int>& connectedNodes) const;
		int GetGroupSize(int id) const;

    private:
        void ProcessConnections();

    private:
        ConnectionMap m_connections;
	};

}}
