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

    static std::vector<Coordinate> multiplyColumnCoordinates(std::vector<Coordinate> points, matrix matrix);

    static void multiplyRowCoordinates(std::vector<Node*> nodes, matrix matrix);

    static matrix convertGLFloatToMatrix(float *pFloat, int rows, int columns);

    static bool inverse4x4(const float *pFloat, float *inv);

private:

    static matrix getMatrixOfZeros(int rows, int columns);
};

#endif //CSG_MATRIXOPERATION_H
