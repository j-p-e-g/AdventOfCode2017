#include "stdafx.h"

#include <iostream>

#include "CodeUtil.h"
#include "December02.h"

using namespace AdventOfCode::December02;

MatrixCheckSum::MatrixCheckSum(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool MatrixCheckSum::ParseLine(const std::string& inputLine)
{
    std::vector<std::string> stringVec = CodeUtils::CodeUtil::SplitStringBySpace(inputLine);
    std::vector<int> intVec;

    bool success = CodeUtils::CodeUtil::ConvertStringVectorToIntVector(stringVec, intVec);
    if (success)
    {
        AddRow(intVec);
        return true;
    }

    return false;
}

void MatrixCheckSum::OutputResultToConsole() const
{
    std::cout << "December02: result = " << GetCheckSum() << std::endl;
}

void MatrixCheckSum::AddRow(const MatrixRow& row)
{
    m_matrix.push_back(row);
}

int MatrixCheckSum::GetRowCheckSum(const MatrixRow& row)
{
	if (row.empty())
	{
		return 0;
	}

	// For each row, determine the difference between the largest value and the smallest value;
	int min = INT_MAX;
	int max = -INT_MAX;
	for (auto& val : row)
	{
		if (val < min)
		{
			min = val;
		}
		if (val > max)
		{
			max = val;
		}
	}

	return max - min;
}

int MatrixCheckSum::GetMatrixCheckSum(const Matrix& matrix)
{
	// the checksum is the sum of all of these differences.

	int sum = 0;
	for (auto& row : matrix)
	{
		sum += GetRowCheckSum(row);
	}

	return sum;
}

int MatrixCheckSum::GetCheckSum() const
{
    return MatrixCheckSum::GetMatrixCheckSum(m_matrix);
}
