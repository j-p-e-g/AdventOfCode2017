#include "stdafx.h"

#include "AdventOfCodeBase.h"
#include "CodeUtil.h"

using namespace AdventOfCode;
bool AdventOfCodeBase::ReadFile(const std::string& fileName)
{
    std::stringstream content;
    bool success = CodeUtils::CodeUtil::ReadFile(fileName, content);
    if (!success)
    {
        return false;
    }

    std::string line;
    while (std::getline(content, line))
    {
        success = ParseLine(line) && success;
    }

    // returns true iff the entire file could be parsed
    return success;
}

