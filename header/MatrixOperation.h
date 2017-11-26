#ifndef CSG_MATRIXOPERATION_H
#define CSG_MATRIXOPERATION_H


#include <vector>
#include "Coordinate.h"
#include "Node.h"

typedef std::vector<std::vector<float>> matrix;

class MatrixOperation {
public:
    static matrix multiply(matrix matrix1, matrix matrix2);

    static void multiplyColumnCoordinates(std::vector<Node*> nodes, matrix matrix);

    static void multiplyRowCoordinates(std::vector<Node*> nodes, matrix matrix);

private:
    static matrix getMatrixOfZeros(int rows, int columns);
};

#endif //CSG_MATRIXOPERATION_H
