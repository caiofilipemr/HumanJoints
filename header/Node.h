#ifndef CSG_NODE_H
#define CSG_NODE_H

#include <vector>
#include "Coordinate.h"

class Node {
    Coordinate coordinate;
    std::vector<Node*> children;

public:
    Node();
    Node(Coordinate c);

    Coordinate getCoordinate() const;
    std::vector<Node*> getChildren() const;

    void setCoordinate(Coordinate coordinate);
    void appendChild(Node *node);
};


#endif //CSG_NODE_H
