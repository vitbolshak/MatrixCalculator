#ifndef MATRIXCALCULATOR_MATRIXFILEOPERATOR_H
#define MATRIXCALCULATOR_MATRIXFILEOPERATOR_H

#include "matrix.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class MatrixFileOperator
{
public:
    template<class T>
    static Matrix<T> ReadMatrix(const std::string& path, char sep = ' ')
    {
        std::vector<std::vector<T>> resultContainer;

        std::ifstream file(path);
        if (!file)
        {
            throw std::invalid_argument("Failed to open file " + path);
        }

        for (std::string line; std::getline(file, line);)
        {
            std::stringstream ss(line);
            std::vector<T> row;

            for (std::string item; std::getline(ss, item, sep);)
            {
                if (item.empty())
                {
                    continue;
                }
                T element;
                if (std::stringstream(item) >> element)
                {
                    row.push_back(element);
                }
                else
                {
                    throw std::invalid_argument("Failed to read matrix element from file " + path);
                }
            }
            resultContainer.push_back(std::move(row));
        }

        return Matrix<T>{resultContainer};
    }

    template<class T>
    static void WriteMatrix(const std::string& path, const Matrix<T>& matrix)
    {
        std::ofstream file(path, std::ios_base::app);
        if (!file)
        {
            throw std::invalid_argument("Failed to open file " + path);
        }

        const auto[rowCount, colCount] = matrix.GetShape();
        file << "Matrix with shape " << rowCount << " x " << colCount << ":\n";
        file << matrix << std::endl;
    }
};


#endif //MATRIXCALCULATOR_MATRIXFILEOPERATOR_H
