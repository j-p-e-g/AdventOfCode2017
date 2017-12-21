#pragma once

#include "AdventOfCodeBase.h"
#include "CodeUtil.h"

#include <bitset>
#include <map>
#include <vector>

/*
    https://adventofcode.com/2017/day/14

    Part 1:

    The disk in question consists of a 128x128 grid; each square of the grid is either free or used. On this disk, the state of the grid is tracked by the bits in a sequence of knot hashes.

    A total of 128 knot hashes are calculated, each corresponding to a single row in the grid; each hash contains 128 bits which correspond to individual grid squares. Each bit of a hash indicates whether that square is free (0) or used (1).

    The hash inputs are a key string (your puzzle input), a dash, and a number from 0 to 127 corresponding to the row.
    
        For example, if your key string were flqrgnkx, then the first row would be given by the bits of the knot hash of flqrgnkx-0, the second row from the bits of the knot hash of flqrgnkx-1, and so on until the last row, flqrgnkx-127.

    The output of a knot hash is traditionally represented by 32 hexadecimal digits; each of these digits correspond to 4 bits, for a total of 4 * 32 = 128 bits. To convert to bits, turn each hexadecimal digit to its equivalent binary value, high-bit first: 0 becomes 0000, 1 becomes 0001, e becomes 1110, f becomes 1111, and so on; a hash that begins with a0c2017... in hexadecimal would begin with 10100000110000100000000101110000... in binary.

    Continuing this process, the first 8 rows and columns for key flqrgnkx appear as follows, using # to denote used squares, and . to denote free ones:

        ##.#.#..-->
        .#.#.#.#
        ....#.#.
        #.#.##.#
        .##.#...
        ##..#..#
        .#...#..
        ##.#.##.-->
        |      |
        V      V

        In this example, 8108 squares are used across the entire 128x128 grid.

    Given your actual key string, how many squares are used?
*/

namespace AdventOfCode {
namespace December14 {

    typedef std::bitset<32> BitElem;
    typedef std::vector<BitElem> BitRow;

    class BitField
    {
    public:
        BitField() {};
        BitField(const BitRow& array) {};
        void AddBitElement(const BitElem& bitElem);
        int GetSize() const { return static_cast<int>(m_bitRow.size()); }
        BitElem At(int i) const { return m_bitRow[i]; }
        BitRow GetVector() const { return m_bitRow; }
        std::string ToString() const;

    private:
        BitRow m_bitRow;
    };

    typedef std::map<CodeUtils::Point, bool> BitMap;

    class DiskDefragmenter
        : protected AdventOfCodeBase
    {
    public:
        DiskDefragmenter() {};
        DiskDefragmenter(const std::string& fileName);
        ~DiskDefragmenter() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        static bool ParseToBitfield(const std::string& input, BitField& bitfield);
        static bool ConvertHexStringToBitField(const std::string& hexString, BitField& bitfield);
        int GetNumUsedSquaresInGrid() const;

        void SetBit(const CodeUtils::Point& point, bool bit);
        bool GetBit(const CodeUtils::Point& point) const;
        std::string GetRowAsString(int rowId) const;

    protected:
        BitMap m_bitMap;
        const int m_numRows = 128;
        const int m_numColumns = 128;
    };

}}
