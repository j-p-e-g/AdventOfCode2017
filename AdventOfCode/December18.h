#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/18

    Part 1:

    It seems like the assembly is meant to operate on a set of registers that are each named with a single letter and that can each hold a single integer. You suppose each register should start with a value of 0.

    There aren't that many instructions, so it shouldn't be hard to figure out what they do. Here's what you determine:

    snd X plays a sound with a frequency equal to the value of X.
    set X Y sets register X to the value of Y.
    add X Y increases register X by the value of Y.
    mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
    mod X Y sets register X to the remainder of dividing the value contained in register X by the value of Y (that is, it sets X to the result of X modulo Y).
    rcv X recovers the frequency of the last sound played, but only when the value of X is not zero. (If it is zero, the command does nothing.)
    jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)

    Many of the instructions can take either a register (a single letter) or a number. The value of a register is the integer it contains; the value of a number is that number.

    After each jump instruction, the program continues with the instruction to which the jump jumped. After any other instruction, the program continues with the next instruction. Continuing (or jumping) off either end of the program terminates it.

    For example:

        set a 1
        add a 2
        mul a a
        mod a 5
        snd a
        set a 0
        rcv a
        jgz a -1
        set a 1
        jgz a -2

        The first four instructions set a to 1, add 2 to it, square it, and then set it to itself modulo 5, resulting in a value of 4.
        Then, a sound with frequency 4 (the value of a) is played.
        After that, a is set to 0, causing the subsequent rcv and jgz instructions to both be skipped (rcv because a is 0, and jgz because a is not greater than 0).
        Finally, a is set to 1, causing the next jgz instruction to activate, jumping back two instructions to another jump, which jumps again to the rcv, which ultimately triggers the recover operation.

        At the time the recover operation is executed, the frequency of the last sound played is 4.

    What is the value of the recovered frequency (the value of the most recently played sound) the first time a rcv instruction is executed with a non-zero value?
*/

namespace AdventOfCode {
namespace December18 {

    struct CharOrNumber
    {
        CharOrNumber(const std::string& str);

        char id = '0';
        int value = 0;
        bool isValid = false;
        bool isChar = false;
    };

    class RegisterDuet;

    class RegisterCommand
    {
    public:
        RegisterCommand(const std::string& _command)
            : command(_command)
        {
        }

    public:
        virtual bool Apply(RegisterDuet& rd);

    protected:
        std::string command;
    };

    class RegisterCommandSingle
        : public RegisterCommand
    {
    public:
        RegisterCommandSingle(const std::string& _command, const CharOrNumber& _param)
            : RegisterCommand(_command)
            , param(_param)
        {
        }

    protected:
        CharOrNumber param;
    };

    class RegisterCommandDouble
        : public RegisterCommand
    {
    public:
        RegisterCommandDouble(const std::string& _command, const CharOrNumber& _param1, const CharOrNumber& _param2)
            : RegisterCommand(_command)
            , param1(_param1)
            , param2(_param2)
        {
        }

    protected:
        CharOrNumber param1;
        CharOrNumber param2;
    };

    // single-param commands
    class RegisterSnd
        : public RegisterCommandSingle
    {
    public:
        RegisterSnd(const CharOrNumber& _param)
            : RegisterCommandSingle("snd", _param)
        {
        }

    public:
        bool Apply(RegisterDuet& rd) override;
    };

    class RegisterRcv
        : public RegisterCommandSingle
    {
    public:
        RegisterRcv(const CharOrNumber& _param)
            : RegisterCommandSingle("rcv", _param)
        {
        }

    public:
        bool Apply(RegisterDuet& rd) override;
    };

    // double-param commands
    class RegisterSet
        : public RegisterCommandDouble
    {
    public:
        RegisterSet(const CharOrNumber& _id, const CharOrNumber& _param)
            : RegisterCommandDouble("set", _id, _param)
        {
        }

    public:
        bool Apply(RegisterDuet& rd) override;
    };

    class RegisterAdd
        : public RegisterCommandDouble
    {
    public:
        RegisterAdd(const CharOrNumber& _id, const CharOrNumber& _param)
            : RegisterCommandDouble("add", _id, _param)
        {
        }

    public:
        bool Apply(RegisterDuet& rd) override;
    };

    class RegisterMul
        : public RegisterCommandDouble
    {
    public:
        RegisterMul(const CharOrNumber& _id, const CharOrNumber& _param)
            : RegisterCommandDouble("mul", _id, _param)
        {
        }

    public:
        bool Apply(RegisterDuet& rd) override;
    };

    class RegisterMod
        : public RegisterCommandDouble
    {
    public:
        RegisterMod(const CharOrNumber& _id, const CharOrNumber& _param)
            : RegisterCommandDouble("mod", _id, _param)
        {
        }

    public:
        bool Apply(RegisterDuet& rd) override;
    };

    class RegisterJgz
        : public RegisterCommandDouble
    {
    public:
        RegisterJgz(const CharOrNumber& _param1, const CharOrNumber& _param2)
            : RegisterCommandDouble("jgz", _param1, _param2)
        {
        }

    public:
        bool Apply(RegisterDuet& rd) override;
    };


    // main class
    class RegisterDuet
        : protected AdventOfCodeBase
    {
    public:
        RegisterDuet() {};
        RegisterDuet(const std::string& fileName);
        ~RegisterDuet() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        bool ParseCommand(const std::string& command, const CharOrNumber& param1, const CharOrNumber& param2);
        bool ExecuteCommands();
        void SetCurrentIndex(int index) { m_currentIndex = index; }
        int GetCurrentIndex() const { return m_currentIndex; }
        void SetFrequency(long long freq) { m_lastFrequency = freq; }
        long long GetFrequency() const { return m_lastFrequency; }
        void SetRegisterValue(char id, long long value);
        long long GetRegisterValue(char id) const;
        void SetRecoveredFrequency(long long freq) { m_lastRecoveredFrequency = freq; }
        long long GetRecoveredFrequency() const { return m_lastRecoveredFrequency; }

    private:
        std::vector<std::shared_ptr<RegisterCommand>> m_commands;
        std::map<char, long long> m_registers;
        long long m_lastFrequency = -1;
        int m_currentIndex = -1;
        long long m_lastRecoveredFrequency = -1;
    };

}}
