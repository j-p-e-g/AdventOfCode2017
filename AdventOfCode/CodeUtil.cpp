#include "stdafx.h"
#include "CodeUtil.h"

#include <iostream>
#include <fstream>

using namespace CodeUtils;

bool CodeUtil::ReadFile(const std::string& filePath, std::stringstream& fileContents, int recursionDepth)
{
    std::ifstream file;
    file.open(filePath);
    if (!file.is_open())
    {
        if (recursionDepth < MaxRecursionDepth)
        {
            if (!ReadFile("../" + filePath, fileContents, recursionDepth + 1))
            {
                return false;
            }
        }
        else
        {
            std::cerr << "Unable to open file " << filePath << std::endl;
            return false;
        }
    }

    std::string line;
    while (std::getline(file, line))
    {
        fileContents << line << std::endl;
    }
    file.close();

    return true;
}

std::vector<std::string> CodeUtil::SplitStringBySpace(const std::string& input)
{
	std::vector<std::string> elements;

	// read input into stream
	std::stringstream ss(input);

	// read stream into buffer
	std::string buf;
	while (ss >> buf)
	{
		elements.push_back(buf);
	}

	return elements;
}

bool CodeUtil::SplitStringByRegex(const std::string& input, std::vector<std::string>& output, std::regex regex)
{
    std::string suffix = input;
    std::smatch match;
    while (std::regex_search(suffix, match, regex))
    {
        output.push_back(match[match.size()-1].str());
        suffix = match.suffix();
    }

    output.push_back(suffix);

    return true;
}

bool CodeUtil::ConvertStringVectorToIntVector(const std::vector<std::string>& input, std::vector<int>& result)
{
    for (const auto& str : input)
    {
        int value = -1;
        if (!ReadStringToInt(str, value, true))
        {
            return false;
        }

        result.push_back(atoi(str.c_str()));
    }

    return result.size() == input.size();
}

bool CodeUtil::ReadStringToInt(const std::string& input, int& number, bool allowNegative)
{
    std::regex regex("\\s*(-?\\d+)\\s*");
    if (!allowNegative)
    {
        regex = "\\s*(\\d+)\\s*";
    }

    std::smatch match;
    if (!std::regex_match(input, match, regex))
    {
        return false;
    }

    number = atoi(match.str().c_str());
    return true;
}
