#pragma once

#include "December13.h"

/*
    https://adventofcode.com/2017/day/13

    Part 2:

    Now, you need to pass through the firewall without being caught - easier said than done.

    You can't control the speed of the packet, but you can delay it any number of picoseconds. For each picosecond you delay the packet before beginning your trip, all security scanners move one step. You're not in the firewall during this time; you don't enter layer 0 until you stop delaying the packet.

    In the example above, if you delay 10 picoseconds (picoseconds 0 - 9), you won't get caught:

        State after delaying:
         0   1   2   3   4   5   6
        [ ] [S] ... ... [ ] ... [ ]
        [ ] [ ]         [ ]     [ ]
        [S]             [S]     [S]
        [ ]             [ ]

        Picosecond 10:
         0   1   2   3   4   5   6
        ( ) [S] ... ... [ ] ... [ ]
        [ ] [ ]         [ ]     [ ]
        [S]             [S]     [S]
        [ ]             [ ]

         0   1   2   3   4   5   6
        ( ) [ ] ... ... [ ] ... [ ]
        [S] [S]         [S]     [S]
        [ ]             [ ]     [ ]
        [ ]             [ ]


        Picosecond 11:
         0   1   2   3   4   5   6
        [ ] ( ) ... ... [ ] ... [ ]
        [S] [S]         [S]     [S]
        [ ]             [ ]     [ ]
        [ ]             [ ]

         0   1   2   3   4   5   6
        [S] (S) ... ... [S] ... [S]
        [ ] [ ]         [ ]     [ ]
        [ ]             [ ]     [ ]
        [ ]             [ ]


        Picosecond 12:
         0   1   2   3   4   5   6
        [S] [S] (.) ... [S] ... [S]
        [ ] [ ]         [ ]     [ ]
        [ ]             [ ]     [ ]
        [ ]             [ ]

         0   1   2   3   4   5   6
        [ ] [ ] (.) ... [ ] ... [ ]
        [S] [S]         [S]     [S]
        [ ]             [ ]     [ ]
        [ ]             [ ]


        Picosecond 13:
         0   1   2   3   4   5   6
        [ ] [ ] ... (.) [ ] ... [ ]
        [S] [S]         [S]     [S]
        [ ]             [ ]     [ ]
        [ ]             [ ]

         0   1   2   3   4   5   6
        [ ] [S] ... (.) [ ] ... [ ]
        [ ] [ ]         [ ]     [ ]
        [S]             [S]     [S]
        [ ]             [ ]


        Picosecond 14:
         0   1   2   3   4   5   6
        [ ] [S] ... ... ( ) ... [ ]
        [ ] [ ]         [ ]     [ ]
        [S]             [S]     [S]
        [ ]             [ ]

         0   1   2   3   4   5   6
        [ ] [ ] ... ... ( ) ... [ ]
        [S] [S]         [ ]     [ ]
        [ ]             [ ]     [ ]
        [S]             [S]


        Picosecond 15:
        0   1   2   3   4   5   6
        [ ] [ ] ... ... [ ] (.) [ ]
        [S] [S]         [ ]     [ ]
        [ ]             [ ]     [ ]
        [S]             [S]

        0   1   2   3   4   5   6
        [S] [S] ... ... [ ] (.) [ ]
        [ ] [ ]         [ ]     [ ]
        [ ]             [S]     [S]
        [ ]             [ ]


        Picosecond 16:
        0   1   2   3   4   5   6
        [S] [S] ... ... [ ] ... ( )
        [ ] [ ]         [ ]     [ ]
        [ ]             [S]     [S]
        [ ]             [ ]

        0   1   2   3   4   5   6
        [ ] [ ] ... ... [ ] ... ( )
        [S] [S]         [S]     [S]
        [ ]             [ ]     [ ]
        [ ]             [ ]

        Because all smaller delays would get you caught, the fewest number of picoseconds you would need to delay to get through safely is 10.

    What is the fewest number of picoseconds that you need to delay the packet to pass through the firewall without being caught?
*/

namespace AdventOfCode {
namespace December13 {

    struct TimeBlock
    {
        TimeBlock(int _start, int _offset)
            : start(_start)
            , offset(_offset)
        {
        }

        bool operator==(const TimeBlock& other)
        {
            return other.start == start && other.offset == offset;
        }

    public:
        int start;
        int offset;
    };

    class FirewallB
        : public Firewall
    {
    public:
        FirewallB() {};
        FirewallB(const std::string& fileName);
        ~FirewallB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        // upper limit to the maximum number of combinations
        int GetMaxNumberOfGuardCombinations() const;
        void AddTimesBlockedByGuards(std::vector<TimeBlock>& blockedTimes, int maxTime) const;
        int GetMinDelayNeededToAvoidDetection() const;
    };

}}
