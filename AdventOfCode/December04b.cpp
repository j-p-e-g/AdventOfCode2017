#include "stdafx.h"

#include <iostream>
#include <set>

#include "CodeUtil.h"
#include "December04b.h"

using namespace AdventOfCode::December04;

AnagramPassPhraseCheck::AnagramPassPhraseCheck(const std::string& fileName)
    : PassPhraseCheck(fileName)
{
}

void AnagramPassPhraseCheck::OutputResultToConsole() const
{
    std::cout << "December04.b: result = " << CountValidPassPhrases(m_phraseList) << std::endl;
}

bool AnagramPassPhraseCheck::CheckPassPhrase(const std::string& input) const
{
    const std::vector<std::string> elements = CodeUtils::CodeUtil::SplitStringBySpace(input);
    std::set<std::string> uniqueElements;

    for (const auto& elem : elements)
    {
        uniqueElements.emplace(SortLettersInString(elem));
    }

    return elements.size() == uniqueElements.size();
}

std::string AnagramPassPhraseCheck::SortLettersInString(const std::string & input)
{
    std::vector<char> temp;
    for (int k = 0; k < input.length(); k++)
    {
        temp.push_back(input[k]);
    }

    std::sort(temp.begin(), temp.end());

    std::string sortedLetters;
    for (auto c : temp)
    {
        sortedLetters += c;
    }

    return sortedLetters;
}
