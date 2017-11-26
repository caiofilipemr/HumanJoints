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

    void rotateXIfGreaterThenZero(std::vector<Node *> nodes);

    void rotateYIfGreaterThenZero(std::vector<Node *> nodes);

    void rotateZIfGreaterThenZero(std::vector<Node *> nodes);

    matrix calculateXMatrix(float angle, Coordinate translation);

    matrix calculateYMatrix(float angle, Coordinate translation);

    matrix calculateZMatrix(float angle, Coordinate translation);

    double toRadians(float angle) const;
};


#endif //CSG_ROTATIONTRANSFORMATION_H
