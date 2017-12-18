#include "stdafx.h"

#include <iostream>

#include "December02b.h"

using namespace AdventOfCode::December02;

MatrixCheckSumMultiple::MatrixCheckSumMultiple(const std::string& fileName)
    : MatrixCheckSum(fileName)
{
}

bool MatrixCheckSumMultiple::ParseLine(const std::string& inputLine)
{
    return false;
}

void MatrixCheckSumMultiple::OutputResultToConsole() const
{
    std::cout << "December02.b: result = " << GetCheckSum() << std::endl;
}

int MatrixCheckSumMultiple::GetRowCheckSum(const MatrixRow& row) const
{
    if (row.empty())
    {
        return 0;
    }

    // find the two values in each row that are multiples of each other
    for (int k = 0; k < row.size(); k++)
        for (int j = k + 1; j < row.size(); j++)
        {
            int val1 = row[k];
            int val2 = row[j];

            // return the quotient
            if (val1 > val2 && val1 % val2 == 0)
            {
                return (val1 / val2);
            }
            if (val2 > val1 && val2 % val1 == 0)
            {
                return (val2 / val1);
            }
        }

    return 0;
}
