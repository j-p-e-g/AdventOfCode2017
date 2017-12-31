#pragma once

#include "December18.h"

/*
    https://adventofcode.com/2017/day/18

    Part 2:

    This assembly code isn't about sound at all - it's meant to be run twice at the same time.

    Each running copy of the program has its own set of registers and follows the code independently - in fact, the programs don't even necessarily run at the same speed. To coordinate, they use the send (snd) and receive (rcv) instructions:

    snd X sends the value of X to the other program. These values wait in a queue until that program is ready to receive them. Each program has its own message queue, so a program can never receive a message it sent.
    rcv X receives the next value and stores it in register X. If no values are in the queue, the program waits for a value to be sent to it. Programs do not continue to the next instruction until they have received a value. Values are received in the order they are sent.

    Each program also has its own program ID (one 0 and the other 1); the register p should begin with this value.

    For example:

        snd 1
        snd 2
        snd p
        rcv a
        rcv b
        rcv c
        rcv d

        Both programs begin by sending three values to the other. Program 0 sends 1, 2, 0; program 1 sends 1, 2, 1. Then, each program receives a value (both 1) and stores it in a, receives another value (both 2) and stores it in b, and then each receives the program ID of the other program (program 0 receives 1; program 1 receives 0) and stores it in c. Each program now sees a different value in its own copy of register c.

        Finally, both programs try to rcv a fourth time, but no data is waiting for either of them, and they reach a deadlock. When this happens, both programs terminate.

    It should be noted that it would be equally valid for the programs to run at different speeds; for example, program 0 might have sent all three values and then stopped at the first rcv before program 1 executed even its first instruction.

    Once both of your programs have terminated (regardless of what caused them to do so), how many times did program 1 send a value?
*/

namespace AdventOfCode {
namespace December18 {

    class RegisterSoloB;

    class RegisterSndB
        : public RegisterSnd
    {
    public:
        RegisterSndB(const CharOrNumber& _param)
            : RegisterSnd(_param)
        {
        }

    public:
        bool Apply(RegisterSolo& rd) override;
    };

    class RegisterRcvB
        : public RegisterRcv
    {
    public:
        RegisterRcvB(const CharOrNumber& _param)
            : RegisterRcv(_param)
        {
        }

    public:
        bool Apply(RegisterSolo& rd) override;
    };

    class RegisterDuet;

    class RegisterSoloB
        : public RegisterSolo
    {
        enum State
        {
            S_NONE,
            S_RUNNING,
            S_WAITING,
            S_FINISHED
        };

    public:
        RegisterSoloB(int id, const std::shared_ptr<RegisterDuet>& duet);
        ~RegisterSoloB() = default;

    public:
        // RegisterSolo
        bool ExecuteNextCommand() override;
        // ~RegisterSolo

        bool ParseCommand(const std::string& command, const CharOrNumber& param1, const CharOrNumber& param2) override;
        void Send(long long value) override;
        bool SetQueuedValue(char id) override;
        void AddToQueue(long long val);
        int GetSendCount() const;

        bool IsRunning() const { return m_state == S_RUNNING; }
        bool IsFinished() const { return m_state == S_FINISHED; }
        bool IsStalled() const { return m_state == S_WAITING; }

    private:
        int m_id;
        std::vector<long long> m_queue;
        std::shared_ptr<RegisterDuet> m_duet;
        State m_state = S_NONE;
        int m_sendCount = 0;
    };

    class RegisterDuet
        : public RegisterSolo
    {
    public:
        RegisterDuet() {};
        ~RegisterDuet() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        // RegisterSolo
        bool ParseCommand(const std::string& command, const CharOrNumber& param1, const CharOrNumber& param2) override;
        bool ExecuteCommands() override;
        // ~RegisterSolo

        void ReadFile(const std::string& fileName);
        void RegisterProgram(std::shared_ptr<RegisterSoloB>& program);
        void Send(int id, long long value);

    private:
        std::vector<std::shared_ptr<RegisterSoloB>> m_programs;
    };

}}
