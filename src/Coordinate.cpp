#include "../header/Coordinate.h"

Coordinate::Coordinate() : x(0), y(0), z(0), w(1) {

}

Coordinate::Coordinate(float x, float y, float z) : x(x), y(y), z(z), w(1) {

}

Coordinate::Coordinate(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {

}

Coordinate Coordinate::add(Coordinate point) {
    return Coordinate(x + point.x, y + point.y, z + point.z);
}

Coordinate Coordinate::multiply(float multiplier) {
    return Coordinate(x * multiplier, y * multiplier, z * multiplier);
}

Coordinate Coordinate::divide(float divider) {
    return Coordinate(x / divider, y / divider, z / divider);
}

std::vector<std::vector<float>> Coordinate::toColumnArray() {
    return std::vector<std::vector<float>> {{x},
                                            {y},
                                            {z},
                                            {1}};
}

std::vector<std::vector<float>> Coordinate::toRowArray() {
    return std::vector<std::vector<float>>{{x, y, z, 1}};
}

Coordinate Coordinate::fromColumnArray(std::vector<std::vector<float>> point) {
    Coordinate p = Coordinate(point[0][0], point[1][0], point[2][0]);
    return point[3][0] == 1 ? p : p.divide(point[3][0]);
}

Coordinate Coordinate::fromRowArray(std::vector<std::vector<float>> point) {
    Coordinate p = Coordinate(point[0][0], point[0][1], point[0][2]);
    return point[0][3] == 1 ? p : p.divide(point[0][3]);
}

void Coordinate::copy(Coordinate transformedPoint) {
    x = transformedPoint.x;
    y = transformedPoint.y;
    z = transformedPoint.z;
}

Coordinate Coordinate::clone() {
    return Coordinate(x, y, z);
}
