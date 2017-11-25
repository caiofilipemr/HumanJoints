#include "../header/Node.h"

Node::Node() {

}

Node::Node(Coordinate c) : coordinate(c) {

}

Coordinate Node::getCoordinate() const {
    return coordinate;
}

std::vector<Node *> Node::getChildren() const {
    return children;
}

void Node::setCoordinate(Coordinate coordinate) {
    this->coordinate = coordinate;
}

void Node::appendChild(Node *node) {
    this->children.push_back(node);
}
