#include "../header/MatrixOperation.h"

matrix MatrixOperation::multiply(matrix matrix1, matrix matrix2) {
    if (matrix1[0].size() != matrix2.size())
        throw ("Matrix can't be multiplied!");

    matrix result = getMatrixOfZeros(matrix1.size(), matrix2[0].size());
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix2[0].size(); ++j) {
            for (int k = 0; k < matrix1[0].size(); ++k) {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }
    return result;
}

void MatrixOperation::multiplyColumnCoordinates(std::vector<Node*> nodes, matrix matrix) {
    Coordinate transformedCoordinate;
    for (auto node : nodes) {
        transformedCoordinate = Coordinate::fromColumnArray(
                MatrixOperation::multiply(matrix, node->getCoordinate().toColumnArray()));
        node->getCoordinate().copy(transformedCoordinate);
    }
}

std::vector<Coordinate> MatrixOperation::multiplyColumnCoordinates(std::vector<Coordinate> points, matrix matrix) {
    Coordinate transformedCoordinate;
    for (int i = 0; i < points.size(); ++i) {
        transformedCoordinate = Coordinate::fromColumnArray(
                MatrixOperation::multiply(matrix, points[i].toColumnArray()));
        points[i]= transformedCoordinate;
    }
    return points;
}

void MatrixOperation::multiplyRowCoordinates(std::vector<Node*> nodes, matrix matrix) {
    Coordinate transformedCoordinate;
    for (auto node : nodes) {
        transformedCoordinate = Coordinate::fromRowArray(MatrixOperation::multiply(node->getCoordinate().toRowArray(), matrix));
        node->getCoordinate().copy(transformedCoordinate);
    }
}

matrix MatrixOperation::getMatrixOfZeros(int rows, int columns) {
    matrix matrixOfZeros;
    for (int i = 0; i < rows; ++i) {
        matrixOfZeros.push_back(std::vector<float>());
        for (int j = 0; j < columns; j++) {
            matrixOfZeros[i].push_back(0);
        }
    }
    return matrixOfZeros;
}

matrix MatrixOperation::convertGLFloatToMatrix(float *pFloat, int rows, int columns) {
    matrix convertedMatrix;
    for (int i = 0; i < rows; ++i) {
        convertedMatrix.push_back(std::vector<float>());
        for (int j = 0; j < columns; ++j) {
            convertedMatrix[i].push_back(pFloat[i * columns + j]);
        }
    }
    return convertedMatrix;
}

/**
 * https://stackoverflow.com/a/1148405/6062136.
 * @param m
 * @param invOut
 * @return
 */
bool MatrixOperation::inverse4x4(const float *m, float *invOut) {
        float inv[16], det;
        int i;

        inv[0] = m[5]  * m[10] * m[15] -
                 m[5]  * m[11] * m[14] -
                 m[9]  * m[6]  * m[15] +
                 m[9]  * m[7]  * m[14] +
                 m[13] * m[6]  * m[11] -
                 m[13] * m[7]  * m[10];

        inv[4] = -m[4]  * m[10] * m[15] +
                 m[4]  * m[11] * m[14] +
                 m[8]  * m[6]  * m[15] -
                 m[8]  * m[7]  * m[14] -
                 m[12] * m[6]  * m[11] +
                 m[12] * m[7]  * m[10];

        inv[8] = m[4]  * m[9] * m[15] -
                 m[4]  * m[11] * m[13] -
                 m[8]  * m[5] * m[15] +
                 m[8]  * m[7] * m[13] +
                 m[12] * m[5] * m[11] -
                 m[12] * m[7] * m[9];

        inv[12] = -m[4]  * m[9] * m[14] +
                  m[4]  * m[10] * m[13] +
                  m[8]  * m[5] * m[14] -
                  m[8]  * m[6] * m[13] -
                  m[12] * m[5] * m[10] +
                  m[12] * m[6] * m[9];

        inv[1] = -m[1]  * m[10] * m[15] +
                 m[1]  * m[11] * m[14] +
                 m[9]  * m[2] * m[15] -
                 m[9]  * m[3] * m[14] -
                 m[13] * m[2] * m[11] +
                 m[13] * m[3] * m[10];

        inv[5] = m[0]  * m[10] * m[15] -
                 m[0]  * m[11] * m[14] -
                 m[8]  * m[2] * m[15] +
                 m[8]  * m[3] * m[14] +
                 m[12] * m[2] * m[11] -
                 m[12] * m[3] * m[10];

        inv[9] = -m[0]  * m[9] * m[15] +
                 m[0]  * m[11] * m[13] +
                 m[8]  * m[1] * m[15] -
                 m[8]  * m[3] * m[13] -
                 m[12] * m[1] * m[11] +
                 m[12] * m[3] * m[9];

        inv[13] = m[0]  * m[9] * m[14] -
                  m[0]  * m[10] * m[13] -
                  m[8]  * m[1] * m[14] +
                  m[8]  * m[2] * m[13] +
                  m[12] * m[1] * m[10] -
                  m[12] * m[2] * m[9];

        inv[2] = m[1]  * m[6] * m[15] -
                 m[1]  * m[7] * m[14] -
                 m[5]  * m[2] * m[15] +
                 m[5]  * m[3] * m[14] +
                 m[13] * m[2] * m[7] -
                 m[13] * m[3] * m[6];

        inv[6] = -m[0]  * m[6] * m[15] +
                 m[0]  * m[7] * m[14] +
                 m[4]  * m[2] * m[15] -
                 m[4]  * m[3] * m[14] -
                 m[12] * m[2] * m[7] +
                 m[12] * m[3] * m[6];

        inv[10] = m[0]  * m[5] * m[15] -
                  m[0]  * m[7] * m[13] -
                  m[4]  * m[1] * m[15] +
                  m[4]  * m[3] * m[13] +
                  m[12] * m[1] * m[7] -
                  m[12] * m[3] * m[5];

        inv[14] = -m[0]  * m[5] * m[14] +
                  m[0]  * m[6] * m[13] +
                  m[4]  * m[1] * m[14] -
                  m[4]  * m[2] * m[13] -
                  m[12] * m[1] * m[6] +
                  m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
                 m[1] * m[7] * m[10] +
                 m[5] * m[2] * m[11] -
                 m[5] * m[3] * m[10] -
                 m[9] * m[2] * m[7] +
                 m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
                 m[0] * m[7] * m[10] -
                 m[4] * m[2] * m[11] +
                 m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] -
                 m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
                  m[0] * m[7] * m[9] +
                  m[4] * m[1] * m[11] -
                  m[4] * m[3] * m[9] -
                  m[8] * m[1] * m[7] +
                  m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
                  m[0] * m[6] * m[9] -
                  m[4] * m[1] * m[10] +
                  m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] -
                  m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)
            return false;

        det = 1.f / det;

        for (i = 0; i < 16; i++)
            invOut[i] = inv[i] * det;

        return true;
}
