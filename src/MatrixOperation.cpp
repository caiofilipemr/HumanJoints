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
