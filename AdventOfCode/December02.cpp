#include "stdafx.h"
#include "December02.h"

using namespace December02;

int CheckSum::GetCheckSum(const MatrixRow& row) const
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

int CheckSum::GetCheckSum(const Matrix& matrix) const
{
	// the checksum is the sum of all of these differences.

	int sum = 0;
	for (auto& row : matrix)
	{
		sum += GetCheckSum(row);
	}

	return sum;
}
