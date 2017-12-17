#include "stdafx.h"
#include "CodeUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

std::vector<std::string> CodeUtil::SplitStringBySpace(std::string input)
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
