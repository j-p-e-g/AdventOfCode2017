#include "stdafx.h"

#include <iostream>

#include "CodeUtil.h"
#include "December08.h"


using namespace AdventOfCode::December08;

ComparisonType Condition::GetComparisonType(const std::string& typeString)
{
	if (typeString == "==")
	{
		return ComparisonType::CT_EQUAL_TO;
	}
	if (typeString == "!=")
	{
		return ComparisonType::CT_NOT_EQUAL_TO;
	}
	if (typeString == ">")
	{
		return ComparisonType::CT_GREATER_THAN;
	}
	if (typeString == "<")
	{
		return ComparisonType::CT_SMALLER_THAN;
	}
	if (typeString == ">=")
	{
		return ComparisonType::CT_GREATER_OR_EQUAL_TO;
	}
	if (typeString == "<=")
	{
		return ComparisonType::CT_SMALLER_OR_EQUAL_TO;
	}
	return ComparisonType::CT_NONE;
}

bool Condition::CheckCondition(int otherValue) const
{
	switch (comparisonType)
	{
	case ComparisonType::CT_EQUAL_TO:
		return otherValue == value;
	case ComparisonType::CT_NOT_EQUAL_TO:
		return otherValue != value;
	case ComparisonType::CT_GREATER_THAN:
		return otherValue > value;
	case ComparisonType::CT_SMALLER_THAN:
		return otherValue < value;
	case ComparisonType::CT_GREATER_OR_EQUAL_TO:
		return otherValue >= value;
	case ComparisonType::CT_SMALLER_OR_EQUAL_TO:
		return otherValue <= value;
	default:
		return false;
	}

}

RegisterCommand::RegisterCommand(const std::string& id, int bonus, Condition condition)
	: m_id(id)
	, m_bonus(bonus)
	, m_condition(condition)
{
	m_isValid = (id != "");
}

RegisterCommand::RegisterCommand(const std::string& commandString)
{
	m_isValid = ParseCommandString(commandString);
}

bool RegisterCommand::ParseCommandString(const std::string& commandString)
{
	const std::vector<std::string> elements = CodeUtils::CodeUtil::SplitStringBySpace(commandString);

	if (elements.size() < 3)
	{
		return false;
	}

	m_id = elements[0];
	m_bonus = atoi(elements[2].c_str());
	if (m_bonus == 0 && elements[2] != "0")
	{
		// bad number
		return false;
	}

	if (elements[1] == "dec")
	{
		m_bonus *= -1;
	}
	else if (elements[1] != "inc")
	{
		m_bonus = 0;
		return false;
	}

	if (elements.size() == 3)
	{
		// no condition, but valid
		return true;
	}

	if (elements.size() != 7)
	{
		// unexpected number of elements when trying to define a condition
		return false;
	}

	if (elements[3] != "if")
	{
		return false;
	}

	m_condition.id = elements[4];

	m_condition.comparisonType = Condition::GetComparisonType(elements[5]);
	if (m_condition.comparisonType == ComparisonType::CT_NONE)
	{
		return false;
	}

	m_condition.value = atoi(elements[6].c_str());
	if (m_condition.value == 0 && elements[6] != "0")
	{
		// bad number
		return false;
	}

	return true;
}

// -------------------------------------
// RegisterHandler
// -------------------------------------

RegisterHandler::RegisterHandler(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool RegisterHandler::ParseLine(const std::string& inputLine)
{
    return ApplyCommand(inputLine);
}

void RegisterHandler::OutputResultToConsole() const
{
    std::cout << "December08: result = " << GetLargestRegisterEntry() << std::endl;
}

bool RegisterHandler::ApplyCommand(const std::string& commandString)
{
	RegisterCommand command(commandString);

	if (!command.IsValid())
	{
		return false;
	}

	if (command.HasCondition())
	{
		const Condition condition = command.GetCondition();
		int conditionValue = 0;

		const auto& found = m_register.find(condition.id);
		if (found != m_register.end())
		{
			conditionValue = found->second;
		}

		if (!condition.CheckCondition(conditionValue))
		{
			// valid but condition not applicable -> no effect
			return true;
		}
	}

	// no condition or condition applies
	int value = 0;

	const auto& found = m_register.find(command.GetId());
	if (found == m_register.end())
	{
		m_register.emplace(command.GetId(), 0);
	}
	else
	{
		value = found->second;
	}

	m_register[command.GetId()] = value + command.GetBonus();
	return true;
}

bool RegisterHandler::RegisterExists(const std::string& id) const
{
	return m_register.find(id) != m_register.end();
}

int RegisterHandler::GetValue(const std::string& id) const
{
	const auto& found = m_register.find(id);
	if (found != m_register.end())
	{
		return found->second;
	}

	return 0;
}

int RegisterHandler::GetLargestRegisterEntry() const
{
	int maxValue = INT_MIN;

	for (const auto& entry : m_register)
	{
		if (entry.second > maxValue)
		{
			maxValue = entry.second;
		}
	}

	return maxValue;
}
