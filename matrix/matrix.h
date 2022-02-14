#ifndef MATRIXCALCULATOR_MATRIX_H
#define MATRIXCALCULATOR_MATRIX_H

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

struct Shape
{
    size_t rowCount;
    size_t colCount;

    bool operator!=(Shape other)
    {
        return std::tie(rowCount, colCount) != std::tie(other.rowCount, other.colCount);
    }
};

template <class T>
class Matrix
{
public:
    explicit Matrix(const std::vector<std::vector<T>>& container): _container(container) {};

    Shape GetShape() const
    {
        return {_container.size(), _container[0].size()};
    };

    std::vector<T> GetRow(size_t i) const
    {
        if (i < 0 || i >= GetShape().rowCount)
        {
            throw std::out_of_range("Row index is out of matrix range");
        }

        return _container[i];
    };

    std::vector<T> GetColumn(size_t j) const
    {
        if (j < 0 || j >= GetShape().colCount)
        {
            throw std::out_of_range("Column index is out of matrix range");
        }

        std::vector<T> column;
        size_t rowCount = GetShape().rowCount;
        column.reserve(rowCount);
        for (size_t i = 0; i < rowCount; ++i)
        {
            column.push_back(_container[i][j]);
        }

        return column;
    };

    T& At(size_t i, size_t j)
    {
        if (i < 0 || i >= GetShape().rowCount)
        {
            throw std::out_of_range("Row index is out of matrix range");
        }

        if (j < 0 || j >= GetShape().colCount)
        {
            throw std::out_of_range("Column index is out of matrix range");
        }

        return _container[i][j];
    };

    const T& At(size_t i, size_t j) const
    {
        if (i < 0 || i >= GetShape().rowCount)
        {
            throw std::out_of_range("Row index is out of matrix range");
        }

        if (j < 0 || j >= GetShape().colCount)
        {
            throw std::out_of_range("Column index is out of matrix range");
        }

        return _container[i][j];
    };

    Matrix<T> operator+(const Matrix<T>& other) const
    {
        if (GetShape() != other.GetShape())
        {
            throw std::range_error("Unable to sum matrices with different shapes");
        }

        const auto[rowCount, colCount] = GetShape();
        return CreateNewMatrix(rowCount, colCount, [this, other](size_t i, size_t j)
        {
            return _container[i][j] + other._container[i][j];
        });
    }

    Matrix<T> operator-(const Matrix<T>& other) const
    {
        if (GetShape() != other.GetShape())
        {
            throw std::range_error("Unable to subtract matrices with different shapes");
        }

        const auto[rowCount, colCount] = GetShape();
        return CreateNewMatrix(rowCount, colCount, [this, other](size_t i, size_t j)
        {
            return _container[i][j] - other._container[i][j];
        });
    }

    Matrix<T> operator*(const Matrix<T>& other) const
    {
        if (GetShape().colCount != other.GetShape().rowCount)
        {
            throw std::range_error("Matrices shapes are unacceptable for multiplication");
        }

        return CreateNewMatrix(GetShape().rowCount, other.GetShape().colCount, [this, other](size_t i, size_t j)
        {
            T newElement = 0;
            for (size_t idx = 0; idx < GetShape().colCount; ++idx)
            {
                newElement += _container[i][idx] * other._container[idx][j];
            }
            return newElement;
        });
    }

    Matrix<T> operator*(T factor) const
    {
        const auto[rowCount, colCount] = GetShape();
        return CreateNewMatrix(rowCount, colCount, [this, factor](size_t i, size_t j)
        {
            return _container[i][j] * factor;
        });
    }

    friend Matrix<T> operator*(T factor, const Matrix<T>& matrix)
    {
        return matrix * factor;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
    {
        os << std::fixed << std::setprecision(3);
        for (const auto& row : matrix._container)
        {
            for (const auto& item : row)
            {
                os << std::setw(9) << item << ' ';
            }
            os << '\n';
        }
        os << std::endl;

        return os;
    };

private:
    /*
     * CreateNewMatrix generates new matrix with given shape and according to new element generating function
     * generateNewElementFunc takes two indexes as params and says how to create element on given indexes
     */
    template<class function>
    Matrix<T> CreateNewMatrix(size_t rowCount, size_t colCount, function generateNewElementFunc) const
    {
        std::vector<std::vector<T>> resultContainer;

        resultContainer.reserve(rowCount);
        for (size_t i = 0; i < rowCount; ++i)
        {
            std::vector<T> row;
            row.reserve(colCount);
            for (size_t j = 0; j < colCount; ++j)
            {
                row.push_back(generateNewElementFunc(i, j));
            }
            resultContainer.push_back(std::move(row));
        }

        return Matrix{resultContainer};
    }

private:
    std::vector<std::vector<T>> _container;
};

#endif //MATRIXCALCULATOR_MATRIX_H
