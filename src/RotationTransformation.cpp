#include "../header/RotationTransformation.h"

RotationTransformation::RotationTransformation(float x, float y, float z) : x(x), y(y), z(z) { }

void RotationTransformation::transform(std::vector<Node *> nodes) {
    rotateXIfGreaterThenZero(nodes);
    rotateYIfGreaterThenZero(nodes);
    rotateZIfGreaterThenZero(nodes);
}

void RotationTransformation::rotateXIfGreaterThenZero(std::vector<Node *> nodes) {
    if (x > 0) {
        Coordinate translation = nodes.front()->getCoordinate();
        MatrixOperation::multiplyColumnCoordinates(nodes, calculateXMatrix(x, translation));
    }
}

void RotationTransformation::rotateYIfGreaterThenZero(std::vector<Node *> nodes) {
    if (y > 0) {
        Coordinate translation = nodes.front()->getCoordinate();
        MatrixOperation::multiplyColumnCoordinates(nodes, calculateYMatrix(y, translation));
    }
}

void RotationTransformation::rotateZIfGreaterThenZero(std::vector<Node *> nodes) {
    if (z > 0) {
        Coordinate translation = nodes.front()->getCoordinate();
        MatrixOperation::multiplyColumnCoordinates(nodes, calculateZMatrix(z, translation));
    }
}

matrix RotationTransformation::calculateXMatrix(float angle, Coordinate translation) {
    angle = toRadians(angle);
    matrix translationMatrixNegative = {{1, 0, 0, -translation.x},
                                        {0, 1, 0, -translation.y},
                                        {0, 0, 1, -translation.z},
                                        {0, 0, 0, 1}};
    matrix translationMatrixPositive = {{1, 0, 0, translation.x},
                                        {0, 1, 0, translation.y},
                                        {0, 0, 1, translation.z},
                                        {0, 0, 0, 1}};
    matrix xMatrix = {{1, 0,          0,           0},
                      {0, cosf(angle), -sinf(angle), 0},
                      {0, sinf(angle), cosf(angle),  0},
                      {0, 0,          0,           1}};
    return MatrixOperation::multiply(translationMatrixPositive,
                                     MatrixOperation::multiply(xMatrix, translationMatrixNegative));
}

matrix RotationTransformation::calculateYMatrix(float angle, Coordinate translation) {
    angle = toRadians(angle);
    matrix translationMatrixNegative = {{1, 0, 0, -translation.x},
                                        {0, 1, 0, -translation.y},
                                        {0, 0, 1, -translation.z},
                                        {0, 0, 0, 1}};
    matrix translationMatrixPositive = {{1, 0, 0, translation.x},
                                        {0, 1, 0, translation.y},
                                        {0, 0, 1, translation.z},
                                        {0, 0, 0, 1}};
    matrix yMatrix = {{cosf(angle),  0, sinf(angle), 0},
                      {0,           1, 0,          0},
                      {-sinf(angle), 0, cosf(angle), 0},
                      {0,           0, 0,          1}};
    return MatrixOperation::multiply(translationMatrixPositive,
                                     MatrixOperation::multiply(yMatrix, translationMatrixNegative));
}

matrix RotationTransformation::calculateZMatrix(float angle, Coordinate translation) {
    angle = toRadians(angle);
    matrix translationMatrixNegative = {{1, 0, 0, -translation.x},
                                        {0, 1, 0, -translation.y},
                                        {0, 0, 1, -translation.z},
                                        {0, 0, 0, 1}};
    matrix translationMatrixPositive = {{1, 0, 0, translation.x},
                                        {0, 1, 0, translation.y},
                                        {0, 0, 1, translation.z},
                                        {0, 0, 0, 1}};
    matrix zMatrix = {{cosf(angle), -sinf(angle), 0, 0},
                      {sinf(angle), cosf(angle),  0, 0},
                      {0,          0,           1, 0},
                      {0,          0,           0, 1}};
    return MatrixOperation::multiply(translationMatrixPositive,
                                     MatrixOperation::multiply(zMatrix, translationMatrixNegative));
}

double RotationTransformation::toRadians(float angle) const { return angle * M_PI / 180; }
