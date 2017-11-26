#include "../header/RotationTransformation.h"

RotationTransformation::RotationTransformation(float x, float y, float z) : x(x), y(y), z(z) { }

void RotationTransformation::transform(std::vector<Node *> nodes) {
    rotateXIfDiffThenZero(nodes);
    rotateYIfDiffThenZero(nodes);
    rotateZIfDiffThenZero(nodes);
}

std::vector<Coordinate> RotationTransformation::transform(std::vector<Coordinate> points) {
    points = rotateXIfDiffThenZero(points);
    points = rotateYIfDiffThenZero(points);
    points = rotateZIfDiffThenZero(points);
    return points;
}

void RotationTransformation::rotateXIfDiffThenZero(std::vector<Node *> nodes) {
    if (x != 0) {
        Coordinate translation = nodes.front()->getCoordinate();
        MatrixOperation::multiplyColumnCoordinates(nodes, calculateXMatrix(x, translation));
    }
}

std::vector<Coordinate> RotationTransformation::rotateXIfDiffThenZero(std::vector<Coordinate> points) {
    if (x != 0) {
        Coordinate translation = points.front();
        points = MatrixOperation::multiplyColumnCoordinates(points, calculateXMatrix(x, translation));
    }
    return points;
}

void RotationTransformation::rotateYIfDiffThenZero(std::vector<Node *> nodes) {
    if (y != 0) {
        Coordinate translation = nodes.front()->getCoordinate();
        MatrixOperation::multiplyColumnCoordinates(nodes, calculateYMatrix(y, translation));
    }
}

std::vector<Coordinate> RotationTransformation::rotateYIfDiffThenZero(std::vector<Coordinate> points) {
    if (y != 0) {
        Coordinate translation = points.front();
        points = MatrixOperation::multiplyColumnCoordinates(points, calculateYMatrix(y, translation));
    }
    return points;
}

void RotationTransformation::rotateZIfDiffThenZero(std::vector<Node *> nodes) {
    if (z != 0) {
        Coordinate translation = nodes.front()->getCoordinate();
        MatrixOperation::multiplyColumnCoordinates(nodes, calculateZMatrix(z, translation));
    }
}

std::vector<Coordinate> RotationTransformation::rotateZIfDiffThenZero(std::vector<Coordinate> points) {
    if (z != 0) {
        Coordinate translation = points.front();
        points = MatrixOperation::multiplyColumnCoordinates(points, calculateZMatrix(z, translation));
    }
    return points;
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