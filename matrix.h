#ifndef MATRIXCALCULATOR_MATRIX_H
#define MATRIXCALCULATOR_MATRIX_H

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

template <class T>
class Matrix
{
public:
    explicit Matrix(const std::vector<std::vector<T>>& container): _container(container) {};

    std::pair<size_t, size_t> GetShape() const
    {
        return {_container.size(), _container[0].size()};
    };

    std::vector<T> GetRow(size_t i) const
    {
        if (i < 0 || i >= GetShape().first)
        {
            throw std::out_of_range("Row index is out of matrix range");
        }

        return _container[i];
    };

    std::vector<T> GetColumn(size_t j) const
    {
        if (j < 0 || j >= GetShape().second)
        {
            throw std::out_of_range("Column index is out of matrix range");
        }

        std::vector<T> column;
        size_t n = GetShape().first;
        column.reserve(n);
        for (size_t i = 0; i < n; ++i)
        {
            column.push_back(_container[i][j]);
        }

        return column;
    };

    T& At(size_t i, size_t j)
    {
        if (i < 0 || i >= GetShape().first)
        {
            throw std::out_of_range("Row index is out of matrix range");
        }

        if (j < 0 || j >= GetShape().second)
        {
            throw std::out_of_range("Column index is out of matrix range");
        }

        return _container[i][j];
    };

    const T& At(size_t i, size_t j) const
    {
        if (i < 0 || i >= GetShape().first)
        {
            throw std::out_of_range("Row index is out of matrix range");
        }

        if (j < 0 || j >= GetShape().second)
        {
            throw std::out_of_range("Column index is out of matrix range");
        }

        return _container[i][j];
    };

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
    {
        os << std::fixed << std::setprecision(3);
        for (const auto& row : matrix._container)
        {
            for (const auto& item : row)
            {
                os << std::setw(9) << item;
            }
            os << '\n';
        }
        os << std::endl;

        return os;
    };

private:
    std::vector<std::vector<T>> _container;
};

#endif //MATRIXCALCULATOR_MATRIX_H
