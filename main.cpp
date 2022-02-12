#include "matrix/matrix.h"
#include "matrix/matrix_file_operator.h"

#include <iostream>

using namespace std;

int main()
{
    try
    {
        Matrix<int> matr = MatrixFileOperator::ReadMatrix<int>("matrix.txt", ',');
        MatrixFileOperator::WriteMatrix("new_matrix.txt", matr);
    }

    catch (std::exception& e)
    {
        cout << e.what();
    }

    return 0;
}
