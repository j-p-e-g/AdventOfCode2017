#pragma once

#include <map>
#include <string>
#include <vector>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/8

    Part 1:

    Each instruction consists of several parts: the register to modify, whether to increase or decrease that register's value, the amount by which to increase or decrease it, and a condition. If the condition fails, skip the instruction without modifying the register. The registers all start at 0. The instructions look like this:

        b inc 5 if a > 1
        a inc 1 if b < 5
        c dec -10 if a >= 1
        c inc -20 if c == 10

    These instructions would be processed as follows:

        Because a starts at 0, it is not greater than 1, and so b is not modified.
        a is increased by 1 (to 1) because b is less than 5 (it is 0).
        c is decreased by -10 (to 10) because a is now greater than or equal to 1 (it is 1).
        c is increased by -20 (to -10) because c is equal to 10.

        After this process, the largest value in any register is 1.

    You might also encounter <= (less than or equal to) or != (not equal to). However, the CPU doesn't have the bandwidth to tell you what all the registers are named, and leaves that to you to determine.

    What is the largest value in any register after completing the instructions in your puzzle input?
*/
/*
    Part 2:

    the CPU also needs to know the highest value held in any register during this process so that it can decide how much memory to allocate to these operations. 

        For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).
*/
namespace AdventOfCode {
namespace December08 {

    enum ComparisonType : int
	{
		CT_NONE,
		CT_SMALLER_THAN,
		CT_GREATER_THAN,
		CT_EQUAL_TO,
		CT_NOT_EQUAL_TO,
		CT_SMALLER_OR_EQUAL_TO,
		CT_GREATER_OR_EQUAL_TO
	};

	struct Condition
	{
		std::string id;
		ComparisonType comparisonType = ComparisonType::CT_NONE;
		int value = 0;

	public:
		bool operator ==(const Condition& other) const
		{
			return id == other.id
				&& comparisonType == other.comparisonType
				&& value == other.value;
		}

		bool CheckCondition(int value) const;

		static ComparisonType GetComparisonType(const std::string& typeString);

		bool IsValid() const
		{
			return id != "" && comparisonType != ComparisonType::CT_NONE;
		}

		std::string ToString() const
		{
			const std::string str = "Condition( id: " + id + ", type: " + std::to_string(static_cast<int>(comparisonType)) + ", value: " + std::to_string(value) + " )";

			return str;
		}

		std::wstring ToWString() const
		{
			const std::string str = ToString();

			std::wstring wstr;
			wstr.assign(str.begin(), str.end());

			return wstr;
		}
	};

	class RegisterCommand
	{
	public:
		RegisterCommand() {};
		RegisterCommand(const std::string& id, int bonus, Condition condition);
		RegisterCommand(const std::string& commandString);
		bool ParseCommandString(const std::string& commandString);

	public:
		std::string GetId() const { return m_id; }
		bool IsValid() const { return m_isValid; }
		int GetBonus() const { return m_bonus; }
		Condition GetCondition() const { return m_condition; }

		bool operator ==(const RegisterCommand& other) const
		{
			return m_id == other.m_id
				&& m_bonus == other.m_bonus
				&& m_condition == other.m_condition
				&& m_isValid == other.m_isValid;
		}

		bool HasCondition() const
		{
			return m_condition.IsValid();
		}

		std::string ToString() const
		{
			const std::string str = "Command( id: " + m_id + ", bonus: " + std::to_string(m_bonus) + ", condition: " + m_condition.ToString() + " )";

			return str;
		}

		std::wstring ToWString() const
		{
			const std::string str = ToString();

			std::wstring wstr;
			wstr.assign(str.begin(), str.end());

			return wstr;
		}

	private:
		std::string m_id;
		int m_bonus = 0;
		Condition m_condition;
		bool m_isValid = false;

	};

	class RegisterHandler
        : protected AdventOfCodeBase
	{
	public:
		RegisterHandler() {};
        RegisterHandler(const std::string& fileName);
        ~RegisterHandler() = default;

    public:
        // AdventOfCodeBase
        bool ParseLine(const std::string& inputLine) override;
        void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

	public:
		bool ApplyCommand(const std::string& commandString);
		bool RegisterExists(const std::string& id) const;
		int GetValue(const std::string& id) const;
		int GetLargestRegisterEntry() const;

	private:
		std::map<std::string, int> m_register;
	};
}}
