#pragma once

#include <vector>

namespace Matrix
{
    template<typename T>
    class Matrix
    {
    public:
        void Clear()
        {
            for (auto& row : m_matrix)
            {
                row.clear();
            }

            m_matrix.clear();
        }

        void Set(int x, int y, T value)
        {
            if (x < 0 || y < 0)
            {
                return;
            }

            while (y >= m_matrix.size())
            {
                m_matrix.push_back(std::vector<T>());
            }

            if (x >= m_matrix[y].size())
            {
                for (auto& row : m_matrix)
                {
                    while (x >= row.size())
                    {
                        row.push_back(GetDefaultEntry());
                    }
                }
            }

            SetValue(x, y, value);
        }

        T Get(int x, int y) const
        {
            if (x < 0 || y < 0 || y >= m_matrix.size() || x >= m_matrix[y].size())
            {
                return GetDefaultEntry();
            }

            return m_matrix[y][x];
        }

        int GetHeight() const { return static_cast<int>(m_matrix.size()); }
        int GetWidth() const { return m_matrix.empty() ? 0 : static_cast<int>(m_matrix[0].size()); }

        int CountValue(T value) const
        {
            int count = 0;

            for (const auto& row : m_matrix)
            {
                for (const auto& cell : row)
                {
                    if (cell == value)
                    {
                        count++;
                    }
                }
            }

            return count;
        }

        bool Equals(const Matrix<T>& other)
        {
            if (GetHeight() != other.GetHeight())
            {
                return false;
            }
            if (GetWidth() != other.GetWidth())
            {
                return false;
            }

            for (int x = 0; x < GetWidth(); x++)
            {
                for (int y = 0; y < GetHeight(); y++)
                {
                    if (Get(x, y) != other.Get(x, y))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        void DoHorizontalMirrorFlip()
        {
            // abc    cba
            // def -> fed
            // ghi    ihg
            for (int x = 0; x < GetWidth() / 2; x++)
            {
                for (int y = 0; y < GetHeight(); y++)
                {
                    if (x == GetWidth() - x - 1)
                    {
                        continue;
                    }

                    T copy = Get(x, y);
                    Set(x, y, Get(GetWidth() - x - 1, y));
                    Set(GetWidth() - x - 1, y, copy);
                }
            }
        }

        void DoVerticalMirrorFlip()
        {
            // abc    ghi
            // def -> def
            // ghi    abc
            for (int x = 0; x < GetWidth(); x++)
            {
                for (int y = 0; y < GetHeight() / 2; y++)
                {
                    if (y == GetHeight() - y - 1)
                    {
                        continue;
                    }

                    T copy = Get(x, y);
                    Set(x, y, Get(x, GetHeight() - y - 1));
                    Set(x, GetHeight() - y - 1, copy);
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
            for (int x = 0; x < GetWidth(); x++)
            {
                for (int y = 0; y < x; y++)
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
        void SetValue(int x, int y, T value)
        {
            m_matrix[y][x] = value;
        }

    private:
        std::vector<std::vector<T>> m_matrix;
    };

    class CharMatrix
        : public Matrix<char>
    {
        char GetDefaultEntry() const { return ' '; };
    };
}
