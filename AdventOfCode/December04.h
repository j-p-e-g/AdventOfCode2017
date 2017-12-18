#pragma once

#include <string>
#include <vector>

#include "AdventOfCodeBase.h"
/*
    https://adventofcode.com/2017/day/4

    Part 1:

    A passphrase consists of a series of words (lowercase letters) separated by spaces.

    To ensure security, a valid passphrase must contain no duplicate words.

    For example:

        aa bb cc dd ee is valid.
        aa bb cc dd aa is not valid - the word aa appears more than once.
        aa bb cc dd aaa is valid - aa and aaa count as different words.
*/

namespace AdventOfCode {
namespace December04 {

	class PassPhraseCheck
        : protected AdventOfCodeBase
	{
	public:
		PassPhraseCheck() {};
        PassPhraseCheck(const std::string& fileName);
        ~PassPhraseCheck() = default;

    public:
        // AdventOfCodeBase
        bool ParseLine(const std::string& inputLine) override;
        void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
		virtual bool CheckPassPhrase(const std::string& input) const;
        int CountValidPassPhrases(const std::vector<std::string>& list) const;

    private:
        void AddPassPhrase(const std::string& phrase);

    protected:
        std::vector<std::string> m_phraseList;
	};

}}
