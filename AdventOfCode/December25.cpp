#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December25.h"

using namespace AdventOfCode::December25;

TMBlueprints::TMBlueprints(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
    ExecuteSteps();
}

bool TMBlueprints::ParseLine(const std::string& inputLine)
{
    {
        std::regex regex("\\s*");
        std::smatch match;

        // empty line
        if (std::regex_match(inputLine, match, regex))
        {
            // add previously defined blueprint step
            if (m_newStep.IsValid())
            {
                AddBlueprintStep(m_newStep);
                // replace with invalid step
                m_newStep = BlueprintStep();
            }

            return true;
        }
    }

    {
        // initial state
        std::regex regex("\\s*Begin in state (\\w).\\s*");
        std::smatch match;

        if (std::regex_match(inputLine, match, regex))
        {
            if (match.size() != 2)
            {
                return false;
            }

            m_currentState = match[1].str()[0];
            return true;
        }
    }

    {
        // checksum steps
        std::regex regex("\\s*Perform a diagnostic checksum after (\\d+) steps.\\s*");
        std::smatch match;

        if (std::regex_match(inputLine, match, regex))
        {
            if (match.size() != 2)
            {
                return false;
            }

            if (!CodeUtils::CodeUtil::ReadStringToInt(match[1].str(), m_numSteps, false))
            {
                return false;
            }

            return true;
        }
    }

    {
        // state condition
        std::regex regex("\\s*In state (\\w):\\s*");
        std::smatch match;

        if (std::regex_match(inputLine, match, regex))
        {
            if (match.size() != 2)
            {
                return false;
            }

            m_newStep.stateCondition = match[1].str()[0];

            if (m_newStep.stateCondition < 'A' || m_newStep.stateCondition > 'Z')
            {
                return false;
            }

            return true;
        }
    }

    {
        // value condition
        std::regex regex("\\s*If the current value is (\\d):\\s*");
        std::smatch match;

        if (std::regex_match(inputLine, match, regex))
        {
            if (match.size() != 2)
            {
                return false;
            }

            // add previously defined blueprint step
            if (m_newStep.IsValid())
            {
                AddBlueprintStep(m_newStep);
            }

            if (!CodeUtils::CodeUtil::ReadStringToInt(match[1].str(), m_newStep.valueCondition, false))
            {
                return false;
            }

            if (m_newStep.valueCondition < 0 || m_newStep.valueCondition > 1)
            {
                return false;
            }

            return true;
        }
    }

    {
        // set new value
        std::regex regex("\\s*- Write the value (\\d).\\s*");
        std::smatch match;

        if (std::regex_match(inputLine, match, regex))
        {
            if (match.size() != 2)
            {
                return false;
            }

            if (!CodeUtils::CodeUtil::ReadStringToInt(match[1].str(), m_newStep.newValue, false))
            {
                return false;
            }

            if (m_newStep.newValue < 0 || m_newStep.newValue > 1)
            {
                return false;
            }

            return true;
        }
    }

    {
        // move the cursor
        std::regex regex("\\s*- Move one slot to the (\\w+).\\s*");
        std::smatch match;

        if (std::regex_match(inputLine, match, regex))
        {
            if (match.size() != 2)
            {
                return false;
            }

            const std::string direction = match[1].str();
            if (direction == "left")
            {
                m_newStep.newDirection = -1;
                return true;
            }

            if (direction == "right")
            {
                m_newStep.newDirection = 1;
                return true;
            }

            return false;
        }
    }

    {
        // set new state
        std::regex regex("\\s*- Continue with state (\\w).\\s*");
        std::smatch match;

        if (std::regex_match(inputLine, match, regex))
        {
            if (match.size() != 2)
            {
                return false;
            }

            m_newStep.newState = match[1].str()[0];

            if (m_newStep.newState < 'A' || m_newStep.newState > 'Z')
            {
                return false;
            }

            return true;
        }
    }

    return false;
}

void TMBlueprints::ExecuteSteps()
{
    for (int k = m_numSteps; k > 0; k--)
    {
        for (const auto& step : m_blueprintSteps)
        {
            if (step.stateCondition == m_currentState
                && step.valueCondition == GetCurrentValue())
            {
                SetCurrentValue(step.newValue);
                ShiftIndex(step.newDirection);
                SetCurrentState(step.newState);
                break;
            }
        }
    }
}

int TMBlueprints::GetCurrentValue() const
{
    const auto& found = m_tapeValues.find(m_currentIndex);
    if (found == m_tapeValues.end())
    {
        return 0;
    }

    return found->second;
}

void TMBlueprints::SetCurrentValue(int value)
{
    auto& found = m_tapeValues.find(m_currentIndex);
    if (found == m_tapeValues.end())
    {
        m_tapeValues.emplace(m_currentIndex, value);
        return;
    }

    found->second = value;
}

void TMBlueprints::OutputResultToConsole() const
{
    std::cout << "December25: result = " << GetCheckSum() << std::endl;
}

int TMBlueprints::GetCheckSum() const
{
    int count = 0;
    for (const auto& v : m_tapeValues)
    {
        count += v.second;
    }

    return count;
}
