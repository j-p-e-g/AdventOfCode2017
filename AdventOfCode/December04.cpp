#include "stdafx.h"
#include "CodeUtil.h"
#include "December04.h"

#include <set>

using namespace December04;

bool PassPhraseCheck::CheckPassPhrase(std::string input) const
{
	const std::vector<std::string> elements = CodeUtils::CodeUtil::SplitStringBySpace(input);
	std::set<std::string> uniqueElements;

	for (const auto& elem : elements)
	{
		uniqueElements.emplace(elem);
	}

	return elements.size() == uniqueElements.size();
}

int PassPhraseCheck::CountValidPassPhrases(std::vector<std::string> list) const
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
