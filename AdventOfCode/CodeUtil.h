#pragma once

#include <sstream>
#include <string>
#include <vector>

/*
*/
namespace CodeUtils
{
	class CodeUtil
	{
	public:
        static bool ReadFile(const std::string& filePath, std::stringstream& fileContents, int recursionDepth = 0);
        static std::vector<std::string> CodeUtil::SplitStringBySpace(std::string input);

    private:
        static const int MaxRecursionDepth = 3;
    };
}
