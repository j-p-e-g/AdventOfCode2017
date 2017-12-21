#pragma once

#include <regex>
#include <sstream>
#include <string>
#include <vector>

/*
*/
namespace CodeUtils
{
    struct Point
    {
    public:
        Point(int _x, int _y)
            : x(_x)
            , y(_y)
        {
        }

        bool IsValid()
        {
            return x >= 0 && y >= 0;
        }

        bool operator <(const Point& other) const
        {
            return x < other.x || x == other.x && y < other.y;
        }

        bool operator <=(const Point& other) const
        {
            return x < other.x || x == other.x && y <= other.y;
        }

        bool operator >(const Point& other) const
        {
            return !(*this <= other);
        }

        bool operator >=(const Point& other) const
        {
            return (*this == other) || (*this > other);
        }

        bool operator ==(const Point& other) const
        {
            return x == other.x && y == other.y;
        }

        void operator +=(const Point& other)
        {
            x += other.x;
            y += other.y;
        }

        std::wstring ToWString() const
        {
            std::string str = "Point( " + std::to_string(x) + ", " + std::to_string(y) + " )";

            std::wstring wstr;
            wstr.assign(str.begin(), str.end());

            return wstr;
        }

    public:
        int x = 0;
        int y = 0;
    };

    const Point InvalidCoord = Point(-1, -1);

    class CodeUtil
	{
	public:
        static bool ReadFile(const std::string& filePath, std::stringstream& fileContents, int recursionDepth = 0);
        static std::vector<std::string> SplitStringBySpace(const std::string& input);
        static bool SplitStringByRegex(const std::string& input, std::vector<std::string>& output, std::regex regex);
        static bool ConvertStringVectorToIntVector(const std::vector<std::string>& input, std::vector<int>& result);
        static bool ReadStringToInt(const std::string& input, int& number, bool allowNegative);
        static void ReadIntToString(const int input, std::string& result);

    private:
        static const int MaxRecursionDepth = 3;
    };
}
