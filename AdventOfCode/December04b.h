#pragma once

#include "December04.h"

/*
    https://adventofcode.com/2017/day/4

    Part 2:

    For added security, yet another system policy has been put in place. Now, a valid passphrase must contain no two words that are anagrams of each other - that is, a passphrase is invalid if any word's letters can be rearranged to form any other word in the passphrase.

    For example:

        abcde fghij is a valid passphrase.
        abcde xyz ecdab is not valid - the letters from the third word can be rearranged to form the first word.
        a ab abc abd abf abj is a valid passphrase, because all letters need to be used when forming another word.
        iiii oiii ooii oooi oooo is valid.
        oiii ioii iioi iiio is not valid - any of these words can be rearranged to form any other word.

    Under this new system policy, how many passphrases are valid?
*/
namespace AdventOfCode {
namespace December04 {

    class AnagramPassPhraseCheck
        : public PassPhraseCheck
    {
    public:
        AnagramPassPhraseCheck() {};
        AnagramPassPhraseCheck(const std::string& fileName);
        ~AnagramPassPhraseCheck() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        virtual bool CheckPassPhrase(const std::string& input) const override;
        static std::string SortLettersInString(const std::string& input);
    };

}}
