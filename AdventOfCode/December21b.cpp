#include "stdafx.h"

#include <iostream>

#include "CoordPoint.h"
#include "December21b.h"
#include "Matrix.h"

using namespace AdventOfCode::December21;

PixelPatternB::PixelPatternB(const std::string& fileName)
    : PixelPattern()
{
    ReadFile(fileName);
}

void PixelPatternB::OutputResultToConsole() const
{
    std::cout << "December21.b: result = " << CountActivePixels() << std::endl;
}

bool PixelPatternB::ProcessRules(int numIterations)
{
    int remainingIterations = ApplyRulesToMatrix(m_pattern, numIterations, true);

    std::cout << "      final matrix size after " << numIterations << " iterations: " << m_pattern->GetWidth() << std::endl;
    return (remainingIterations == 0);
}

int PixelPatternB::ApplyRulesToMatrix(std::shared_ptr<Matrix::CharMatrix>& matrix, int numIterations, bool first)
{
    if (numIterations <= 0)
    {
        // nothing else to do
        std::cout << "Invalid numIterations " << numIterations << "!" << std::endl;
        return -1;
    }

    const bool was4x4 = (matrix->GetWidth() == 4 && matrix->GetHeight() == 4);
    const std::string startPattern = DescribeMatrix(matrix);

    int remainingIterations = numIterations;

    if (was4x4)
    {
        auto& foundPattern = m_4x4Transformations.find(startPattern);
        if (foundPattern == m_4x4Transformations.end())
        {
            // try the rotations instead
            const auto& foundRotation = m_4x4Rotations.find(startPattern);
            if (foundRotation != m_4x4Rotations.end())
            {
                foundPattern = m_4x4Transformations.find(foundRotation->second);
            }
        }

        if (foundPattern != m_4x4Transformations.end())
        {
            std::string pattern;
            for (int k = numIterations; k > 0; k--)
            {
                const auto& foundIterations = foundPattern->second.find(k);
                if (foundIterations != foundPattern->second.end())
                {
                    pattern = foundIterations->second;
                    remainingIterations = numIterations - k;
                    break;
                }
            }

            if (remainingIterations < numIterations)
            {
                matrix->Clear();
                CreateMatrix(pattern, matrix);

                if (remainingIterations == 0)
                {
                    return remainingIterations;
                }
            }
        }
    }

    if (matrix->GetWidth() >= 2 && matrix->GetWidth() <= 3)
    {
        if (!ApplyRulesToSubMatrix(matrix))
        {
            return -1;
        }

        if (first && remainingIterations > 1)
        {
            return ApplyRulesToMatrix(matrix, remainingIterations - 1, false);
        }

        return remainingIterations - 1;
    }

    // try to split into submatrices of size 4, 2 or 3
    std::map<Coord::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;
    if ((was4x4 || !SplitMatrix(matrix, 4, subMatrices))
        && !SplitMatrix(matrix, 2, subMatrices)
        && !SplitMatrix(matrix, 3, subMatrices))
    {
        return -1;
    }

    int newRemainingIterations = -1;
    for (auto& m : subMatrices)
    {
        newRemainingIterations = ApplyRulesToMatrix(m.second, remainingIterations, false);

        if (newRemainingIterations < 0)
        {
            return -1;
        }
    }

    remainingIterations = newRemainingIterations;

    int oldMatrixSize = matrix->GetWidth();
    if (!CombineMatrices(subMatrices, matrix))
    {
        return -1;
    }

    if (remainingIterations > 0)
    {
        remainingIterations = ApplyRulesToMatrix(matrix, remainingIterations, false);
        if (remainingIterations < 0)
        {
            return -1;
        }
    }

    if (was4x4)
    {
        const std::string targetPattern = DescribeMatrix(matrix);
        auto& foundPattern = m_4x4Transformations.find(startPattern);

        if (foundPattern == m_4x4Transformations.end())
        {
            std::map<int, std::string> patternMap;
            patternMap.emplace(numIterations, targetPattern);
            m_4x4Transformations.emplace(startPattern, patternMap);

            // store all rotations
            std::shared_ptr<Matrix::CharMatrix> startMatrix = std::make_shared<Matrix::CharMatrix>();
            CreateMatrix(startPattern, startMatrix);

            std::set<std::string> rotations;
            GatherAllDescriptions(startMatrix, rotations);

            for (const auto& rot : rotations)
            {
                if (rot != startPattern)
                {
                    m_4x4Rotations.emplace(rot, startPattern);
                }
            }
        }
        else
        {
            foundPattern->second.emplace(numIterations, targetPattern);
        }
    }

    return remainingIterations;
}

