#ifndef MATRIXCALCULATOR_MATRIXMATH_H
#define MATRIXCALCULATOR_MATRIXMATH_H

#include "matrix/matrix.h"

class MatrixMath
{
public:
    template<class T>
    static Matrix<T> Transpose(const Matrix<T>& matrix)
    {
        std::vector<std::vector<T>> resultContainer;
        for (size_t j = 0; j < matrix.GetShape().colCount; ++j)
        {
            resultContainer.push_back(matrix.GetColumn(j));
        }

        return Matrix<T>{resultContainer};
    }

    template<class T>
    static T Trace(const Matrix<T>& matrix)
    {
        if (matrix.GetShape().rowCount != matrix.GetShape().colCount)
        {
            throw std::range_error("Unable to calculate trace of non square matrix");
        }

        T trace = 0;
        for (size_t i = 0; i < matrix.GetShape().rowCount; ++i)
        {
            trace += matrix.At(i, i);
        }

        return trace;
    }


};



#endif //MATRIXCALCULATOR_MATRIXMATH_H
