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
        static bool CodeUtil::ConvertStringVectorToIntVector(const std::vector<std::string>& input, std::vector<int>& result);

    private:
        static const int MaxRecursionDepth = 3;
    };
}
