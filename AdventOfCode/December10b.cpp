#include "stdafx.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "December10b.h"

using namespace AdventOfCode::December10;

ComplexKnotHash::ComplexKnotHash(const std::string& fileName)
    : SimpleKnotHash()
{
    ReadFile(fileName);
}

bool ComplexKnotHash::ParseLine(const std::string& inputLine)
{
    /*
    First, from now on, your input should be taken not as a list of numbers, but as a string of bytes instead. Unless otherwise specified, convert characters to bytes using their ASCII codes. This will allow you to handle arbitrary ASCII strings, and it also ensures that your input lengths are never larger than 255.
    */
    std::vector<int> asciiInput;
    asciiInput.reserve(static_cast<int>(inputLine.length() + m_bonusSequenceOfLengths.size()));

    ConvertStringToAsciiVector(inputLine, asciiInput);

    // add bonus sequence of lengths
    for (const auto& bonus : m_bonusSequenceOfLengths)
    {
        asciiInput.push_back(bonus);
    }

    /*
    Second, instead of merely running one round like you did above, run a total of 64 rounds, using the same length sequence in each round. The current position and skip size should be preserved between rounds.
    */
    HashProcessValues hpv;
    for (int k = 0; k < 64; k++)
    {
        ApplyInput(asciiInput, hpv);
    }

    return true;
}

void ComplexKnotHash::OutputResultToConsole() const
{
    std::cout << "December10.b: result = " << GetKnotHashHexValue() << std::endl;
}

void ComplexKnotHash::ConvertStringToAsciiVector(const std::string& input, std::vector<int>& output)
{
    for (char c : input)
    {
        output.push_back(c);
    }
}

bool ComplexKnotHash::ReduceToDenseHash(const std::vector<int>& sparseHash, std::vector<int>& denseHash)
{
    // length needs to be a multiple of 16
    if (sparseHash.size() % 16 != 0)
    {
        return false;
    }

    denseHash.reserve(sparseHash.size() / 16);

    int count = 0;
    int xorValue = -1;

    for (const auto& val : sparseHash)
    {
        if (count == 0)
        {
            xorValue = val;
        }
        else
        {
            xorValue ^= val;
        }
        count++;

        if (count == 16)
        {
            denseHash.push_back(xorValue);
            count = 0;
        }
    }

    if (sparseHash.size() / 16 != denseHash.size())
    {
        return false;
    }

    return true;
}

void ComplexKnotHash::ConvertVectorToHexValue(const std::vector<int>& hash, std::string& hexString)
{
    std::stringstream stream;
    for (const auto& value : hash)
    {
        if (value < 16)
        {
            stream << '0';
        }
        stream << std::hex << value;
    }

    hexString = stream.str();
}

std::string ComplexKnotHash::GetKnotHashHexValue() const
{
    std::vector<int> denseHash;
    if (!ReduceToDenseHash(m_list, denseHash))
    {
        std::cerr << "December10.b: ERROR ReduceToDenseHash failed" << std::endl;
        return "";
    }

    std::string hexValue;
    ConvertVectorToHexValue(denseHash, hexValue);
    return hexValue;
}
