#include "matrix/matrix.h"
#include "matrix/matrix_file_operator.h"
#include "matrix_math/matrix_math.h"

#include <iostream>

using namespace std;

int main()
{
    try
    {
        Matrix<int> matr = MatrixFileOperator::ReadMatrix<int>("matrix.txt", ',');
        cout << matr;
        cout << MatrixMath::Trace(matr);
        cout << MatrixMath::Transpose(matr);
    }

    catch (std::exception& e)
    {
        cout << e.what();
    }

    return 0;
}
