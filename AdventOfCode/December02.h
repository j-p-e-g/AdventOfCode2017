#pragma once

#include <string>
#include <vector>

#include "AdventOfCodeBase.h"

/*
	https://adventofcode.com/2017/day/2

    Part 1:

	The spreadsheet consists of rows of apparently-random numbers. To make sure the recovery process is on the right track, they need you to calculate the spreadsheet's checksum. For each row, determine the difference between the largest value and the smallest value; the checksum is the sum of all of these differences.

	For example, given the following spreadsheet:

	    5 1 9 5
	    7 5 3
	    2 4 6 8

	    The first row's largest and smallest values are 9 and 1, and their difference is 8.
	    The second row's largest and smallest values are 7 and 3, and their difference is 4.
	    The third row's difference is 6.

	    In this example, the spreadsheet's checksum would be 8 + 4 + 6 = 18.
*/

namespace AdventOfCode {
namespace December02 {

    typedef std::vector<int> MatrixRow;
	typedef std::vector<MatrixRow> Matrix;

	class MatrixCheckSum
        : protected AdventOfCodeBase
	{
	public:
		MatrixCheckSum() {};
        MatrixCheckSum(const Matrix& matrix);
        MatrixCheckSum(const std::string& fileName);
        ~MatrixCheckSum() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        int GetCheckSum() const;

		virtual int GetRowCheckSum(const MatrixRow& row) const;
		int GetMatrixCheckSum(const Matrix& matrix) const;

    public:
        void AddRow(const MatrixRow& row);

    private:
        Matrix m_matrix;
	};

}}
