#include "stdafx.h"

#include <iostream>

#include "December01b.h"

using namespace AdventOfCode::December01;

CircularCheckSum::CircularCheckSum(const std::string& fileName)
    : CheckSum(fileName)
{
}

bool CircularCheckSum::ParseLine(const std::string& inputLine)
{
    CheckSum::ParseLine(inputLine);

    // has to of even length
    if (m_inputValue.length() % 2 != 0)
    {
        return false;
    }

    return true;
}

void CircularCheckSum::OutputResultToConsole() const
{
    std::cout << "December01.b: result = " << ComputeSumForCaptchaString(m_inputValue) << std::endl;
}

int CircularCheckSum::ComputeSumForCaptchaString(const std::string& captchaString)
{
    if (captchaString.length() % 2 == 1)
    {
        return -1;
    }

    const int captchaLength = static_cast<int>(captchaString.length());
    const int offset = captchaLength / 2;

    int sum = 0;
    for (int k = 0; k < offset; k++)
    {
        const char current = captchaString[k];
        const char halfwayAround = captchaString[(k + offset) % captchaLength];

        int currentDigit = CharToInt(current);
        int halfwayAroundDigit = CharToInt(halfwayAround);
        if (currentDigit == halfwayAroundDigit)
        {
            // applies to both digits
            sum += 2*currentDigit;
        }
    }

    return sum;
}
