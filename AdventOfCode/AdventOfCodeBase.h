#pragma once

#include <string>

/*
The interface shared by all puzzle implementations.
*/
namespace AdventOfCode
{
    class AdventOfCodeBase
    {
    public:
        AdventOfCodeBase() {}
        ~AdventOfCodeBase() = default;

    public:
        virtual void OutputResultToConsole() const = 0;

    protected:
        bool ReadFile(const std::string& fileName);
        virtual bool ParseLine(const std::string& inputLine) = 0;
    };
}
