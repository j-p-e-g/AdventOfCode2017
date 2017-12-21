#include "stdafx.h"

#include <bitset>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "CodeUtil.h"
#include "December10b.h"
#include "December14.h"

using namespace AdventOfCode::December14;

// ----------------------------
// Bitfield
// ----------------------------
void BitField::AddBitElement(const BitElem& bitElem)
{
    m_bitArray.push_back(bitElem);
}

std::string BitField::ToString() const
{
    std::string result;
    for (const auto& val : m_bitArray)
    {
        result += val.to_string();
    }

    return result;
}

// -------------------------------
// DiskDefragmentor
// -------------------------------
DiskDefragmentor::DiskDefragmentor(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool DiskDefragmentor::ParseLine(const std::string& inputLine)
{
    // The hash inputs are a key string (your puzzle input), 
    // a dash, and a number from 0 to 127 corresponding to the row.
    for (int k = 0; k < 128; k++)
    {
        std::string numString;
        CodeUtils::CodeUtil::ReadIntToString(k, numString);
        const std::string input = inputLine + "-" + numString;

        BitField bitfield;
        if (!ParseToBitfield(input, bitfield))
        {
            return false;
        }

        AddBitfield(bitfield);
    }

    return true;
}

void DiskDefragmentor::OutputResultToConsole() const
{
    std::cout << "December14: result = " << GetNumUsedSquaresInGrid() << std::endl;
}

bool DiskDefragmentor::ParseToBitfield(const std::string& input, BitField& bitfield)
{
    AdventOfCode::December10::ComplexKnotHash knotHash;
    knotHash.ParseLine(input);

    std::string hexString = knotHash.GetKnotHashHexValue();

    // pad with leading zeros
    for (int k = 0; k < 32 - hexString.length(); k++)
    {
        hexString = "0" + hexString;
    }

    if (!ConvertHexStringToBitField(hexString, bitfield))
    {
        return false;
    }

    return true;
}

bool DiskDefragmentor::ConvertHexStringToBitField(const std::string& hexString, BitField& bitfield)
{
    for (const auto& c : hexString)
    {
        // invalid format
        if (c < '0' || c > 'f' || c > '9' && c < 'a')
        {
            return false;
        }
    }

    const int blockNum = static_cast<int>(std::ceil(static_cast<double>(hexString.length()) / 8));
    for (int k = 0; k < blockNum; k++)
    {
        // copied from https://stackoverflow.com/questions/18310952/convert-strings-between-hex-format-and-binary-format

        std::stringstream stream;
        stream << std::hex << hexString.substr(k * 8, 8);

        unsigned long number;
        stream >> number;

        bitfield.AddBitElement(BitElem(number));
    }

    return true;
}

void DiskDefragmentor::AddBitfield(const BitField& bitfield)
{
    m_grid.push_back(bitfield);
}

int DiskDefragmentor::GetNumUsedSquaresInGrid() const
{
    int sum = 0;
    for (const auto& bitfield : m_grid)
    {
        for (const auto& bitblock : bitfield.GetVector())
        {
            sum += static_cast<int>(bitblock.count());
        }
    }

    return sum;
}
