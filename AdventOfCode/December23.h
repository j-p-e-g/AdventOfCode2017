#pragma once

#include "December18.h"
//#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/23

    Part 1:

    The code [an experimental coprocessor]'s running seems to be a variant of the kind you saw recently on that tablet (December 18). The general functionality seems very similar, but some of the instructions are different:

    set X Y sets register X to the value of Y.
    sub X Y decreases register X by the value of Y.
    mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
    jnz X Y jumps with an offset of the value of Y, but only if the value of X is not zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)

    Only the instructions listed above are used. The eight registers here, named a through h, all start at 0.

    The coprocessor is currently set to some kind of debug mode, which allows for testing, but prevents it from doing any meaningful work.

    If you run the program (your puzzle input), how many times is the mul instruction invoked?
*/

namespace AdventOfCode {
namespace December23 {

    class RegisterHandler;

    // double-param commands
    class RegisterSub
        : public AdventOfCode::December18::RegisterCommandDouble
    {
    public:
        RegisterSub(const AdventOfCode::December18::CharOrNumber& _id, const AdventOfCode::December18::CharOrNumber& _param)
            : RegisterCommandDouble("sub", _id, _param)
        {
        }

    public:
        bool Apply(AdventOfCode::December18::RegisterBase& rd) override;
    };

    class RegisterJnz
        : public AdventOfCode::December18::RegisterCommandDouble
    {
    public:
        RegisterJnz(const AdventOfCode::December18::CharOrNumber& _id, const AdventOfCode::December18::CharOrNumber& _param)
            : RegisterCommandDouble("jnz", _id, _param)
        {
        }

    public:
        bool Apply(AdventOfCode::December18::RegisterBase& rd) override;
    };

    class RegisterHandler
        : public AdventOfCode::December18::RegisterBase
    {
    public:
        RegisterHandler() {};
        RegisterHandler(const std::string& fileName);
        ~RegisterHandler() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        virtual bool ParseCommand(const std::string& command, const AdventOfCode::December18::CharOrNumber& param1, const AdventOfCode::December18::CharOrNumber& param2) override;
        virtual bool ApplyCurrentCommand() override;
        virtual bool ExecuteCommands() override;

        int GetMultiplierCommandCount() const;
    };

}}
