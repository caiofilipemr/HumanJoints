#ifndef CSG_ROTATIONTRANSFORMATION_H
#define CSG_ROTATIONTRANSFORMATION_H

#include <cmath>
#include "Node.h"
#include "MatrixOperation.h"

class RotationTransformation {
private:
    float x, y, z;

public:
    RotationTransformation(float x, float y, float z);

    void transform(std::vector<Node *> nodes);
    std::vector<Coordinate> transform(std::vector<Coordinate> points);

    void rotateXIfDiffThenZero(std::vector<Node *> nodes);

    std::vector<Coordinate> rotateXIfDiffThenZero(std::vector<Coordinate> points);

    void rotateYIfDiffThenZero(std::vector<Node *> nodes);

    std::vector<Coordinate> rotateYIfDiffThenZero(std::vector<Coordinate> points);

    void rotateZIfDiffThenZero(std::vector<Node *> nodes);

    std::vector<Coordinate> rotateZIfDiffThenZero(std::vector<Coordinate> points);

    matrix calculateXMatrix(float angle, Coordinate translation);

    matrix calculateYMatrix(float angle, Coordinate translation);

    matrix calculateZMatrix(float angle, Coordinate translation);

    double toRadians(float angle) const;
};


#endif //CSG_ROTATIONTRANSFORMATION_H
