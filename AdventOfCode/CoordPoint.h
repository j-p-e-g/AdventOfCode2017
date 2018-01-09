#pragma once

#include <string>

namespace Coord
{
    struct Point
    {
    public:
        Point(int _x, int _y)
            : x(_x)
            , y(_y)
        {
        }

        Point()
            : Point(-1, -1)
        {}

        bool IsValid()
        {
            return x >= 0 && y >= 0;
        }

        void operator =(const Point& other)
        {
            x = other.x;
            y = other.y;
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

        Point operator + (const Point& other) const
        {
            Point temp;
            temp.x = x + other.x;
            temp.y = y + other.y;
            return temp;
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

    // only true in finite maps!
    const Point InvalidCoord = Point(-1, -1);
}
