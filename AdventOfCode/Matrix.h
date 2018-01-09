#pragma once

#include <algorithm>
#include <map>

#include "CoordPoint.h"

namespace Matrix
{
    template<typename T>
    class Matrix
    {
    public:
        void Clear()
        {
            m_matrix.clear();
        }

        void Set(int x, int y, T value)
        {
            Set(Coord::Point(x, y), value);
        }

        void Set(Coord::Point& p, T value)
        {
            auto& found = m_matrix.find(p);
            if (found != m_matrix.end())
            {
                found->second = value;
                return;
            }

            m_matrix.emplace(p, value);

            // update ranges
            m_upperLeft.x  = std::min(p.x, m_upperLeft.x);
            m_upperLeft.y  = std::min(p.y, m_upperLeft.y);
            m_lowerRight.x = std::max(p.x, m_lowerRight.x);
            m_lowerRight.y = std::max(p.y, m_lowerRight.y);

            m_width  = m_lowerRight.x - m_upperLeft.x + 1;
            m_height = m_lowerRight.y - m_upperLeft.y + 1;
        }

        T Get(int x, int y) const
        {
            return Get(Coord::Point(x, y));
        }

        T Get(const Coord::Point& p) const
        {
            const auto& found = m_matrix.find(p);
            if (found != m_matrix.end())
            {
                return found->second;
            }

            return GetDefaultEntry();
        }

        int GetWidth() const
        {
            return m_width;
        }

        int GetHeight() const
        {
            return m_height;
        }

        int GetNumCells() const
        {
            return static_cast<int>(m_matrix.size());
        }

        Coord::Point GetMatrixCenter() const
        {
            int centerX = m_upperLeft.x + (GetWidth() - 1) / 2;
            int centerY = m_upperLeft.y + (GetHeight() - 1) / 2;

            return Coord::Point(centerX, centerY);
        }

        int CountValue(T value) const
        {
            int count = 0;

            for (const auto& cell : m_matrix)
            {
                if (cell.second == value)
                {
                    count++;
                }
            }

            if (value == GetDefaultEntry())
            {
                // also add all empty cells
                int size = GetWidth() * GetHeight();
                count += size - static_cast<int>(m_matrix.size());
            }

            return count;
        }

        bool Equals(const Matrix<T>& other) const
        {
            if (GetNumCells() != other.GetNumCells())
            {
                return false;
            }
            if (GetHeight() != other.GetHeight())
            {
                return false;
            }
            if (GetWidth() != other.GetWidth())
            {
                return false;
            }

            for (const auto& cell : m_matrix)
            {
                if (Get(cell.first) != other.Get(cell.first))
                {
                    return false;
                }
            }

            return true;
        }

        void DoHorizontalMirrorFlip()
        {
            // abc    cba
            // def -> fed
            // ghi    ihg

            // only iterate over left half of the matrix
            int halfPointX = m_lowerRight.x - GetWidth() / 2 + 1;
            for (int x = m_upperLeft.x; x < halfPointX; x++)
            {
                for (int y = m_upperLeft.y; y <= m_lowerRight.y; y++)
                {
                    if (x == halfPointX - x)
                    {
                        continue;
                    }

                    T copy = Get(x, y);
                    Set(x, y, Get(halfPointX - x, y));
                    Set(halfPointX - x, y, copy);
                }
            }
        }

        void DoVerticalMirrorFlip()
        {
            // abc    ghi
            // def -> def
            // ghi    abc

            // only iterate over upper half of the matrix
            int halfPointY = m_lowerRight.y - GetHeight() / 2 + 1;
            for (int x = m_upperLeft.x; x <= m_lowerRight.x; x++)
            {
                for (int y = m_upperLeft.y; y < halfPointY; y++)
                {
                    if (y == halfPointY - y)
                    {
                        continue;
                    }

                    T copy = Get(x, y);
                    Set(x, y, Get(x, halfPointY - y));
                    Set(x, halfPointY - y, copy);
                }
            }
        }

        bool SwapXAndY()
        {
            // only works for square matrices
            if (GetWidth() != GetHeight())
            {
                return false;
            }

            // abc    adg
            // def -> beh
            // ghi    cfi
            for (int x = m_upperLeft.x; x <= m_lowerRight.x; x++)
            {
                for (int y = m_upperLeft.y; y < x; y++)
                {
                    if (x == y)
                    {
                        continue;
                    }

                    T copy = Get(x, y);
                    Set(x, y, Get(y, x));
                    Set(y, x, copy);
                }
            }

            return true;
        }

    protected:
        virtual T GetDefaultEntry() const = 0;

    private:
        std::map<Coord::Point, T> m_matrix;

        int m_width = 0;
        int m_height = 0;
        Coord::Point m_upperLeft  = Coord::Point(0, 0);
        Coord::Point m_lowerRight = Coord::Point(0, 0);
    };

    class CharMatrix
        : public Matrix<char>
    {
    public:
        char GetDefaultEntry() const { return m_defaultEntry; };
        void SetDefaultEntry(char def) { m_defaultEntry = def; }

    private:
        char m_defaultEntry = ' ';
    };
}
