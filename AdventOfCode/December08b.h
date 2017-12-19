#pragma once

#include "December08.h"

/*
    https://adventofcode.com/2017/day/8

    Part 2:

    the CPU also needs to know the highest value held in any register during this process so that it can decide how much memory to allocate to these operations.

        For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).
*/

namespace AdventOfCode {
namespace December08 {

    class RegisterHandlerB
        : public RegisterHandler
    {
    public:
        RegisterHandlerB() {};
        RegisterHandlerB(const std::string& fileName);
        ~RegisterHandlerB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        bool ApplyCommand(const std::string& commandString) override;
        int GetLargestRegisterValueEver() const;

    private:
        int m_maxRegisterValue = INT_MIN;
    };

}}
