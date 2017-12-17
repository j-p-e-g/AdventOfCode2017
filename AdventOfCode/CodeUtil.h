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
        static std::vector<std::string> SplitStringBySpace(const std::string& input);
        static bool ConvertStringVectorToIntVector(const std::vector<std::string>& input, std::vector<int>& result);
        static bool ReadStringToInt(const std::string& input, int& number, bool allowNegative);

    private:
        static const int MaxRecursionDepth = 3;
    };
}
