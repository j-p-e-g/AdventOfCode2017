#pragma once

#include <string>

#include "AdventOfCodeBase.h"

/*
	https://adventofcode.com/2017/day/1

    Part 1:

	The captcha requires you to review a sequence of digits (your puzzle input) and find the sum of all digits that match the next digit in the list. The list is circular, so the digit after the last digit is the first digit in the list.

	For example:

	    1122 produces a sum of 3 (1 + 2) because the first digit (1) matches the second digit and the third digit (2) matches the fourth digit.
	    1111 produces 4 because each digit (all 1) matches the next.
	    1234 produces 0 because no digit matches the next.
	    91212129 produces 9 because the only digit that matches the next one is the last digit, 9.
*/

namespace AdventOfCode {
namespace December01 {

    class CheckSum
        : protected AdventOfCodeBase
    {
    public:
        CheckSum() {};
        CheckSum(const std::string& fileName);
        ~CheckSum() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        int GetNumber() const { return atoi(m_inputValue.c_str()); }
        int ComputeCheckSum() const;

        static int ComputeSumForCaptchaString(const std::string& captchaString);

    protected:
        static int CharToInt(char c);

    protected:
        std::string m_inputValue;
    };

}}
