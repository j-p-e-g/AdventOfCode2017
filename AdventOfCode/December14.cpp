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
// BitField
// ----------------------------
void BitField::AddBitElement(const BitElem& bitElem)
{
    m_bitRow.push_back(bitElem);
}

std::string BitField::ToString() const
{
    std::string result;
    for (const auto& val : m_bitRow)
    {
        result += val.to_string();
    }

    return result;
}

// -------------------------------
// DiskDefragmentor
// -------------------------------
DiskDefragmenter::DiskDefragmenter(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool DiskDefragmenter::ParseLine(const std::string& inputLine)
{
    // The hash inputs are a key string (your puzzle input), 
    // a dash, and a number from 0 to 127 corresponding to the row.
    for (int row = 0; row < m_numRows; row++)
    {
        std::string numString;
        CodeUtils::CodeUtil::ReadIntToString(row, numString);
        const std::string input = inputLine + "-" + numString;

        BitField bitfield;
        if (!ParseToBitfield(input, bitfield))
        {
            return false;
        }

        std::string bitString = bitfield.ToString();
        for (unsigned int column = 0; column < bitString.length(); column++)
        {
            SetBit(Coord::Point(row, column), bitString[column] == '1');
        }
    }

    return true;
}

void DiskDefragmenter::OutputResultToConsole() const
{
    std::cout << "December14.a: result = " << GetNumUsedSquaresInGrid() << std::endl;
}

bool DiskDefragmenter::ParseToBitfield(const std::string& input, BitField& bitfield)
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

bool DiskDefragmenter::ConvertHexStringToBitField(const std::string& hexString, BitField& bitfield)
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

void DiskDefragmenter::SetBit(const Coord::Point& point, bool bit)
{
    m_bitMap.emplace(point, bit);
}

bool DiskDefragmenter::GetBit(const Coord::Point& point) const
{
    const auto& found = m_bitMap.find(point);
    if (found == m_bitMap.end())
    {
        return false;
    }

    return found->second;
}

std::string DiskDefragmenter::GetRowAsString(int rowId) const
{
    std::string str;
    for (int c = 0; c < m_numColumns; c++)
    {
        str += GetBit(Coord::Point(rowId, c)) ? "1" : "0";
    }

    return str;
}

int DiskDefragmenter::GetNumUsedSquaresInGrid() const
{
    int sum = 0;
    for (const auto& point : m_bitMap)
    {
        sum += point.second ? 1 : 0;
    }

    return sum;
}
