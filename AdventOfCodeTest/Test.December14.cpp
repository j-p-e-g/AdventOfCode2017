#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December14.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December14;

    TEST_CLASS(Test_December14)
    {
    public:
        /*
        empty input string
        */
        TEST_METHOD(December14_ConvertHexStringToBitField_empty)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ConvertHexStringToBitField("", bitfield));
            Assert::AreEqual(0, bitfield.GetSize());
        }

        /*
        invalid hex value
        */
        TEST_METHOD(December14_ConvertHexStringToBitField_invalid)
        {
            BitField bitfield;
            Assert::AreEqual(false, DiskDefragmentor::ConvertHexStringToBitField("kk", bitfield));
        }

        /*
        convert single 0
        */
        TEST_METHOD(December14_ConvertHexStringToBitField_singleChar_0)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ConvertHexStringToBitField("0", bitfield));
            Assert::AreEqual(1, bitfield.GetSize());
            Assert::AreEqual(0, static_cast<int>(bitfield.At(0).to_ulong()));
        }

        /*
        convert single e
        */
        TEST_METHOD(December14_ConvertHexStringToBitField_singleChar_e)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ConvertHexStringToBitField("e", bitfield));
            Assert::AreEqual(1, bitfield.GetSize());
            Assert::AreEqual(14, static_cast<int>(bitfield.At(0).to_ulong()));
        }

        /*
         a hash that begins with a0c2017... in hexadecimal would begin with 10100000110000100000000101110000... in binary
        */
        TEST_METHOD(December14_ConvertHexStringToBitField_Aoc_test)
        {
            BitField bitfield;
            // take into account that the bitfield is buffered to a length of 32 bits
            Assert::AreEqual(true, DiskDefragmentor::ConvertHexStringToBitField("a0c20170", bitfield));
            //1010 a
            //0000 0
            //1100 c
            //0010 2
            //0000 0
            //0001 1
            //0111 7
            //0000 (0)
            Assert::AreEqual(1, bitfield.GetSize());
            Assert::AreEqual("10100000110000100000000101110000", bitfield.ToString().c_str());
        }

        /*
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
        */
        /*
        the first 8 columns for key flqrgnkx-0 evaluate to
        ##.#.#..-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_0)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-0", bitfield));
            const std::string str = bitfield.ToString();
            Assert::AreEqual("11010100", str.substr(0, 8).c_str());
        }

        /*
        the first 8 columns for key flqrgnkx-1 evaluate to
        .#.#.#.#-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_1)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-1", bitfield));
            const std::string str = bitfield.ToString();
            Assert::AreEqual("01010101", str.substr(0, 8).c_str());
        }

        /*
        the first 8 columns for key flqrgnkx-2 evaluate to
        ....#.#.-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_2)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-2", bitfield));

            const std::string str = bitfield.ToString();
            Assert::AreEqual("00001010", str.substr(0, 8).c_str());
        }

        /*
        the first 8 columns for key flqrgnkx-3 evaluate to
        #.#.##.#-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_3)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-3", bitfield));

            const std::string str = bitfield.ToString();
            Assert::AreEqual("10101101", str.substr(0, 8).c_str());
        }

        /*
        the first 8 columns for key flqrgnkx-4 evaluate to
        .##.#...-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_4)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-4", bitfield));

            const std::string str = bitfield.ToString();
            Assert::AreEqual("01101000", str.substr(0, 8).c_str());
        }

        /*
        the first 8 columns for key flqrgnkx-5 evaluate to
        ##..#..#-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_5)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-5", bitfield));

            const std::string str = bitfield.ToString();
            Assert::AreEqual("11001001", str.substr(0, 8).c_str());
        }

        /*
        the first 8 columns for key flqrgnkx-6 evaluate to
        .#...#..-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_6)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-6", bitfield));

            const std::string str = bitfield.ToString();
            Assert::AreEqual("01000100", str.substr(0, 8).c_str());
        }

        /*
        the first 8 columns for key flqrgnkx-7 evaluate to
        ##.#.##.-->
        */
        TEST_METHOD(December14_ParseToBitfield_Aoc_test_7)
        {
            BitField bitfield;
            Assert::AreEqual(true, DiskDefragmentor::ParseToBitfield("flqrgnkx-7", bitfield));

            const std::string str = bitfield.ToString();
            Assert::AreEqual("11010110", str.substr(0, 8).c_str());
        }

        /*
        In this example, 8108 squares are used across the entire 128x128 grid.  
        */
        TEST_METHOD(December14_GetNumUsedSquaresInGrid_AoC_test)
        {
            DiskDefragmentor test;
            test.ParseLine("flqrgnkx");
            Assert::AreEqual(8108, test.GetNumUsedSquaresInGrid());
        }
    };
}
