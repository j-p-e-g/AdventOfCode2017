#include "stdafx.h"

#include <iostream>
#include <regex>

#include "December01.h"

using namespace AdventOfCode::December01;

CheckSum::CheckSum(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool CheckSum::ParseLine(const std::string& inputLine)
{
    std::regex regex("\\d+");
    if (!std::regex_match(inputLine, regex))
    {
        return false;
    }

    m_inputValue = inputLine;
    return true;
}

void CheckSum::OutputResultToConsole() const
{
    std::cout << "December01: result = " << ComputeSum() << std::endl;
}

int CheckSum::ComputeSum() const
{
    return ComputeSumForCaptchaString(m_inputValue);
}

int CheckSum::ComputeSumForCaptchaString(const std::string& captchaString)
{
    if (captchaString.length() < 2)
    {
        return 0;
    }

    int prevDigit = 0;
    int sum = 0;
    for (auto& c : captchaString)
    {
        int digit = CharToInt(c);
        if (digit == prevDigit)
        {
            sum += digit;
        }

        prevDigit = digit;
    }

    if (prevDigit == CharToInt(captchaString[0]))
    {
        sum += prevDigit;
    }

    return sum;
}

int CheckSum::CharToInt(char c)
{
    return c - '0';
}
