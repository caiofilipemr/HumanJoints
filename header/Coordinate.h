#ifndef CSG_COORDINATE_H
#define CSG_COORDINATE_H

#include <vector>

class Coordinate {
public:
    float x, y, z, w;

    Coordinate();

    Coordinate(float x, float y, float z);

    Coordinate(float x, float y, float z, float w);

    Coordinate add(Coordinate point);

    Coordinate multiply(float multiplier);

    Coordinate divide(float divider);

    std::vector<std::vector<float>> toColumnArray();

    std::vector<std::vector<float>> toRowArray();

    static Coordinate fromColumnArray(std::vector<std::vector<float>> point);

    static Coordinate fromRowArray(std::vector<std::vector<float>> point);

    void copy(Coordinate transformedPoint);

    Coordinate clone();
};


#endif //CSG_COORDINATE_H
