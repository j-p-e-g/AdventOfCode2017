#include "stdafx.h"
#include "CodeUtil.h"
#include "December04.h"

#include <iostream>
#include <set>

using namespace AdventOfCode::December04;

PassPhraseCheck::PassPhraseCheck(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool PassPhraseCheck::ParseLine(const std::string& inputLine)
{
    AddPassPhrase(inputLine);
    return true;
}

void PassPhraseCheck::AddPassPhrase(const std::string& phrase)
{
    m_phraseList.push_back(phrase);
}

void PassPhraseCheck::OutputResultToConsole() const
{
    std::cout << "December04.a: result = " << CountValidPassPhrases(m_phraseList) << std::endl;
}

bool PassPhraseCheck::CheckPassPhrase(const std::string& input) const
{
	const std::vector<std::string> elements = CodeUtils::CodeUtil::SplitStringBySpace(input);
	std::set<std::string> uniqueElements;

	for (const auto& elem : elements)
	{
		uniqueElements.emplace(elem);
	}

	return elements.size() == uniqueElements.size();
}

int PassPhraseCheck::CountValidPassPhrases(const std::vector<std::string>& list) const
{
    int count = 0;
    for (const auto& elem : list)
    {
        if (CheckPassPhrase(elem))
        {
            count++;
        }
    }

    return count;
}
