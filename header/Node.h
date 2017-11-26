#ifndef CSG_NODE_H
#define CSG_NODE_H

#include <vector>
#include "Coordinate.h"

class Node {
    Coordinate coordinate;
    std::vector<Node*> children;
    bool selected;

    void getAllDescendent(Node *pNode, std::vector<Node *> &nodes);

    void verifyCollision(float x, float y, Node *parent, Node *child);
public:

    Node();
    Node(Coordinate c);

    Coordinate &getCoordinate();
    std::vector<Node*> getChildren() const;

    void setCoordinate(Coordinate coordinate);

    void appendChild(Node *node);

    std::vector<Node*> getVectorPath(int indexOffirstChildToGo);

    bool isSelected();

    void verifyCollision(float x, float y);

    Coordinate normalizedPoint(Coordinate &coordinate, Coordinate &getCoordinate);

    float pointLength(Coordinate &coordinate, Coordinate &getCoordinate);
};


#endif //CSG_NODE_H
