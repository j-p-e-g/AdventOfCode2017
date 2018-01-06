#pragma once

#include <vector>

namespace Matrix
{
    template<typename T>
    class Matrix
    {
    public:
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
