#ifndef CSG_NODE_H
#define CSG_NODE_H

#include <vector>
#include "Coordinate.h"

class Node {
    Coordinate coordinate;
    std::vector<Node*> children;
    bool selected;

    void getAllDescendent(Node *pNode, std::vector<Node *> &nodes);

    bool hasCollision(float &x, float &y, Node *parent, Node *child);

    std::vector<Coordinate> getCollisionArea(Coordinate p1, Coordinate p2);

    Coordinate getPoint(Coordinate &p1, Coordinate &p2, float degree) const;

    float smallerX(std::vector<Coordinate> area);

    float biggerX(std::vector<Coordinate> area);

    float smallerY(std::vector<Coordinate> area);

    float biggerY(std::vector<Coordinate> vector);
public:

    Node();
    Node(Coordinate c);

    Coordinate &getCoordinate();
    std::vector<Node*> getChildren() const;

    void setCoordinate(Coordinate coordinate);

    void appendChild(Node *node);

    std::vector<Node*> getVectorPath();

    std::vector<Node*> getVectorPath(int indexOfFirstChildToGo);

    bool isSelected();

    bool verifyCollision(float &x, float &y);

    void deselectedAll();

    Node *getSelectedIfAny();
};


#endif //CSG_NODE_H
