#include "matrix.h"

#include <iostream>

using namespace std;

int main()
{
    std::vector<std::vector<int>> v = {{1, 22}, {38, 4}};
    //constructor
    Matrix matrix(v);
    cout << matrix.At(0,0);
    matrix.At(0, 0) = 999;
    cout << matrix;

    //copy constructor (default)
    const Matrix matrix2(matrix);
    cout << matrix2.At(0,1);
//    matrix2.At(0, 1) = 999;
    cout << matrix2;

    //assign operator (default)
    Matrix matrix3 = matrix2;
    cout << matrix3.At(1,1);
    matrix3.At(1, 1) = 999;
    cout << matrix3;

    return 0;
}
