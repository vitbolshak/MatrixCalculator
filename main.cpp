#include "matrix.h"

#include <iostream>

using namespace std;

int main()
{
    std::vector<std::vector<int>> v = {{1, 22}, {38, 4}};
    //constructor
    Matrix matrix(v);
    cout << matrix;

    //copy constructor (default)
    const Matrix matrix2(matrix);
    cout << matrix2;
    try
    {
        cout << matrix2 + matrix;

        std::vector<std::vector<int>> v2 = {{1 , 2, 3}, {6, 5, 4}};
        std::vector<std::vector<int>> v3 = {{1, 3, 4, 5}, {9, 8, 7, 6}, {6, 4, 2, 5}};
        cout << Matrix(v2) * Matrix(v3);
    }
    catch (std::exception& e)
    {
        cout << e.what();
    }

    return 0;
}
