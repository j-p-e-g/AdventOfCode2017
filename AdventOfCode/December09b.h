#pragma once

#include "December09.h"

/*
    https://adventofcode.com/2017/day/9

    Part 2:

    Now, you're ready to remove the garbage.

    To prove you've removed it, you need to count all of the characters within the garbage. The leading and trailing < and > don't count, nor do any canceled characters or the ! doing the canceling.

        <>, 0 characters.
        <random characters>, 17 characters.
        <<<<>, 3 characters.
        <{!>}>, 2 characters.
        <!!>, 0 characters.
        <!!!>>, 0 characters.
        <{o"i!a,<{i<a>, 10 characters.

    How many non-canceled characters are within the garbage in your puzzle input?
*/

namespace AdventOfCode {
namespace December09 {

    class StreamGarbageRemoval
        : protected StreamOfChars
    {
    public:
        StreamGarbageRemoval(const std::stringstream& stream);
        StreamGarbageRemoval(const std::string& fileName);
        ~StreamGarbageRemoval() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        void ProcessStream(const std::stringstream& stream) override;
        int GetTotalGarbageSize() const;
    };

}}
