#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December21.h"

using namespace AdventOfCode::December21;

PixelPattern::PixelPattern()
{
    m_pattern = std::make_shared<Matrix::CharMatrix>();
    // define initial pattern
    CreateMatrix(".#./..#/###", m_pattern);
}

PixelPattern::PixelPattern(const std::string& fileName)
    : PixelPattern()
{
    ReadFile(fileName);
}

bool PixelPattern::ParseLine(const std::string& inputLine)
{
    std::regex regex("([.#/]+)\\s=>\\s");
    std::vector<std::string> pattern;
    if (!CodeUtils::CodeUtil::SplitStringByRegex(inputLine, pattern, regex)
        || pattern.size() != 2)
    {
        return false;
    }

    // already defined
    if (m_rules.find(pattern[0]) != m_rules.end())
    {
        return false;
    }

    std::shared_ptr<Matrix::CharMatrix> inputMatrix = std::make_shared<Matrix::CharMatrix>();
    std::shared_ptr<Matrix::CharMatrix> outputMatrix = std::make_shared<Matrix::CharMatrix>();

    // invalid pattern
    if (!CreateMatrix(pattern[0], inputMatrix))
    {
        return false;
    }
    if (!CreateMatrix(pattern[1], outputMatrix))
    {
        return false;
    }

    // not a square
    if (inputMatrix->GetWidth() != inputMatrix->GetHeight())
    {
        return false;
    }
    if (outputMatrix->GetWidth() != outputMatrix->GetHeight())
    {
        return false;
    }

    // rule doesn't increase pattern size by exactly 1
    if (inputMatrix->GetHeight() != outputMatrix->GetHeight() - 1)
    {
        return false;
    }

    m_rules.emplace(pattern[0], pattern[1]);
    return true;
}

void PixelPattern::OutputResultToConsole() const
{
    std::cout << "December21: result = " << CountActivePixels() << std::endl;
}

bool PixelPattern::CreateMatrix(const std::string& input, std::shared_ptr<Matrix::CharMatrix>& matrix)
{
    if (matrix == nullptr)
    {
        return false;
    }

    std::regex regex("([^/]+)/");
    std::vector<std::string> rows;
    if (!CodeUtils::CodeUtil::SplitStringByRegex(input, rows, regex))
    {
        return false;
    }

    if (rows.empty())
    {
        return false;
    }

    for (int y = 0; y < rows.size(); y++)
    {
        if (rows[y].length() == 0)
        {
            return false;
        }

        for (int x = 0; x < rows[y].length(); x++)
        {
            matrix->Set(x, y, rows[y][x]);
        }
    }

    return true;
}

bool PixelPattern::ProcessRules(int numIterations)
{
    std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>> subMatrices;

    for (int count = 0; count < numIterations; count++)
    {
        // If the size is evenly divisible by 2, break the pixels up into 2x2 squares, 
        // If it's divisible by 3, break them into 3x3 squares.
        // Otherwise, something is wrong.

        subMatrices.clear();
        if (!SplitMatrix(m_pattern, 2, subMatrices) && !SplitMatrix(m_pattern, 3, subMatrices))
        {
            return false;
        }

        for (auto& m : subMatrices)
        {
            if (!ApplyRulesToSubMatrix(m.second))
            {
                return false;
            }
        }

        if (!CombineMatrices(subMatrices, m_pattern))
        {
            return false;
        }
    }

    return true;
}

bool PixelPattern::SplitMatrix(const std::shared_ptr<Matrix::CharMatrix>& matrix, int size, std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>>& subMatrices)
{
    if (matrix->GetWidth() % size != 0 || matrix->GetHeight() % size != 0)
    {
        return false;
    }

    for (int i = 0; i < matrix->GetHeight() / size; i++)
    {
        for (int j = 0; j < matrix->GetWidth() / size; j++)
        {
            std::shared_ptr<Matrix::CharMatrix> newMatrix = std::make_shared<Matrix::CharMatrix>();

            int xOffset = size * i;
            int yOffset = size * j;
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                    newMatrix->Set(x, y, matrix->Get(x + xOffset, y + yOffset));
                }
            }

            subMatrices.emplace(CodeUtils::Point(i, j), newMatrix);
        }
    }

    return true;
}

bool PixelPattern::ApplyRulesToSubMatrix(std::shared_ptr<Matrix::CharMatrix>& subMatrix)
{
    std::shared_ptr<Matrix::CharMatrix> temp = std::make_shared<Matrix::CharMatrix>();

    for (const auto& rule : m_rules)
    {
        // skip rules that don't match the size
        if (subMatrix->GetWidth() == 2 && rule.first.length() != 5)
        {
            continue;
        }
        if (subMatrix->GetWidth() == 3 && rule.first.length() != 11)
        {
            continue;
        }

        temp->Clear();

        if (!CreateMatrix(rule.first, temp))
        {
            return false;
        }

        // check the base pattern:
        // abc
        // def
        // ghi
        bool matchesPattern = false;
        if (subMatrix->Equals(*temp))
        {
            matchesPattern = true;
        }

        // The most efficient way (no duplicates!) to handle flips and rotation appear to be
        // 1. do all flips for the base pattern -> horizontal -> vertical -> horizontal
        // 2. swap x and y values in the final pattern 
        //    this is easier to do and the result is a flipped rotation, so it's fine
        // 3. do all flips for the rotated pattern

        // abc    cba    ihg    ghi
        // def -> fed -> fed -> def -> swap x and y values
        // ghi    ihg    cba    abc
        //
        // gda    adg    cfi    ifc
        // heb -> beh -> beh -> heb
        // ifc    cfi    adg    gda

        // horizontal flip:
        // cba
        // fed
        // ihg
        if (!matchesPattern)
        {
            temp->DoHorizontalMirrorFlip();
            if (subMatrix->Equals(*temp))
            {
                matchesPattern = true;
            }
        }

        // vertical flip:
        // ihg
        // fed
        // cba
        if (!matchesPattern)
        {
            temp->DoVerticalMirrorFlip();
            if (subMatrix->Equals(*temp))
            {
                matchesPattern = true;
            }
        }

        // another horizontal flip:
        // ghi
        // def
        // abc
        if (!matchesPattern)
        {
            temp->DoHorizontalMirrorFlip();
            if (subMatrix->Equals(*temp))
            {
                matchesPattern = true;
            }
        }

        // swap x and y values
        // gda
        // heb
        // ifc
        if (!matchesPattern)
        {
            temp->SwapXAndY();
            if (subMatrix->Equals(*temp))
            {
                matchesPattern = true;
            }
        }

        // yet another horizontal flip:
        // adg
        // beh
        // cfi
        if (!matchesPattern)
        {
            temp->DoHorizontalMirrorFlip();
            if (subMatrix->Equals(*temp))
            {
                matchesPattern = true;
            }
        }

        // yet another vertical flip:
        // cfi
        // beh
        // adg
        if (!matchesPattern)
        {
            temp->DoVerticalMirrorFlip();
            if (subMatrix->Equals(*temp))
            {
                matchesPattern = true;
            }
        }

        // and finally another horizontal flip:
        // ifc
        // heb
        // gda
        if (!matchesPattern)
        {
            temp->DoHorizontalMirrorFlip();
            if (subMatrix->Equals(*temp))
            {
                matchesPattern = true;
            }
        }

        // did any of these match?
        if (matchesPattern)
        {
            subMatrix->Clear();
            if (!CreateMatrix(rule.second, subMatrix))
            {
                return false;
            }

            return true;
        }

        // otherwise, try the next rule
    }

    // no rule found matching the current matrix
    return false;
}

bool PixelPattern::CombineMatrices(const std::map<CodeUtils::Point, std::shared_ptr<Matrix::CharMatrix>>& subMatrices, std::shared_ptr<Matrix::CharMatrix>& matrix)
{
    if (subMatrices.empty())
    {
        return false;
    }

    // number must be 1 or divisible by 2 or 3
    if (subMatrices.size() == 1)
    {
        matrix = subMatrices.begin()->second;
        return true;
    }

    if (subMatrices.size() % 2 != 0 && subMatrices.size() % 3 != 0)
    {
        return false;
    }

    int size = subMatrices.begin()->second->GetWidth();

    // expected size is 3 or 4
    if (size < 3 || size > 4)
    {
        return false;
    }

    matrix->Clear();
    for (const auto& m : subMatrices)
    {
        int xOffset = size * m.first.x;
        int yOffset = size * m.first.y;

        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                matrix->Set(x + xOffset, y + yOffset, m.second->Get(x, y));
            }
        }
    }

    return true;
}

int PixelPattern::CountActivePixels() const
{
    return m_pattern->CountValue('#');
}
